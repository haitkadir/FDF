#ifndef FDF_H
# define FDF_H
# include <math.h>
# include <fcntl.h>
# include "mlx.h"
# include "./get_next_line/get_next_line.h"
# include "./libft/libft.h"
# include <stdio.h>
// get dimensions
typedef struct t_dimensions
{
    int horizontal;
    int vertical;
}   t_dimensions;
// store mlx options
typedef struct t_mlx
{
    void *mlx;
    void *mlx_win;
    int win_w;
    int win_h;
    int color;
    int zoom;
}   t_mlx;
// mlx data
typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

// functions
int ft_htoi(char *hexa);
int ***get_map_from_fd(char *, t_dimensions *);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void drawline(t_data **, t_mlx, int, int, int, int, int ***);

#endif