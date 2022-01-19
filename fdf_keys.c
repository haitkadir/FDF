#include "fdf.h"


int	key_hook(int keycode, t_data *vars)
{
    if (keycode == 53)
    {
        mlx_destroy_image(vars->mlx, vars->img);
        mlx_destroy_window(vars->mlx, vars->win);
        free(vars->mlx);
        free_3d_arr(vars->map, vars->dimensions);
        exit(0);
    }
    return (0);
}