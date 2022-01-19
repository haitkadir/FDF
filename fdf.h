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
// draw line algorithm's information
typedef struct t_draw
{
    int dx;
    int sx;
    int dy;
    int sy;
    int err;
    int e2;
    int z;
    int z1;
}   t_draw;
// store mlx options
typedef struct t_mlx
{
    int x0;
    int y0;
    int x1;
    int y1;
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

/*-------------------------------- Check Errors ------------------------------*/

void    check_err(int, t_dimensions **);
void    alloc_err(int ***map, t_dimensions **dimensions);

/*-------------------------------- Get Data ----------------------------------*/

int     ft_htoi(char *hexa);
int     get_x_y_len(int, t_dimensions **);
int     ***get_map_from_fd(char *, t_dimensions *);

/*---------------------------- Drawing In Window -----------------------------*/

void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void    drawline(t_data **, t_mlx, int ***);
void    draw(t_data *, int ***, t_dimensions, t_mlx);

#endif