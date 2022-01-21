/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haitkadi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 22:19:29 by haitkadi          #+#    #+#             */
/*   Updated: 2022/01/20 22:19:31 by haitkadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include <math.h>
# include <fcntl.h>
# include "mlx.h"
# include ".././assets/gnl/get_next_line.h"
# include ".././assets/libft/libft.h"

// get dimensions
typedef struct t_dimensions
{
	int	horizontal;
	int	vertical;
}	t_dimensions;
// draw line algorithm's information
typedef struct t_draw
{
	int	dx;
	int	sx;
	int	dy;
	int	sy;
	int	err;
	int	e2;
	int	z;
	int	z1;
}	t_draw;
// store mlx options
typedef struct t_mlx
{
	int	x0;
	int	y0;
	int	x1;
	int	y1;
	int	color;
	int	zoom;
	int	altitude;
}	t_mlx;
// mlx data
typedef struct s_data
{
	void			*img;
	char			*addr;
	void			*mlx;
	void			*win;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	t_dimensions	dimensions;
	int				***map;
}	t_data;

// functions

/*-------------------------------- Check Errors ------------------------------*/

void	err(int err, t_dimensions **dimensions);
void	free_3d_arr(int ***map, t_dimensions dimensions);

/*-------------------------------- Get Data ----------------------------------*/

int		ft_htoi(char *hexa);
int		get_x_y_len(int fd, t_dimensions **dimensions);
int		***get_map_from_fd(char *file_name, t_dimensions *dimensions);

/*---------------------------- Drawing In Window -----------------------------*/

void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void	drawline(t_data **img, t_mlx mlx, int ***map);
void	draw(t_data *img, int ***map, t_dimensions dimensions, t_mlx mlx);

/*---------------------------- Events -----------------------------*/

int		key_hook(int keycode, t_data *vars);

#endif
