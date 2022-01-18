#include "fdf.h"




static void calc_zoom(int *zoom, int width)
{
    if (width > 400)
        *zoom = 2;
    if(width < 300)
        *zoom = 5;
    if (width < 100)
        *zoom = 20;
}

static void fdf(char *file_name)
{
        t_dimensions  dimensions;
        t_mlx mlx;
        void	*mlx_ptr;
        void	*mlx_win;
        t_data	img;

        ft_bzero(&dimensions, sizeof(t_dimensions));
        ft_bzero(&mlx, sizeof(t_mlx));
        int ***map = get_map_from_fd(file_name, &dimensions);
        if(dimensions.horizontal == 0 && dimensions.vertical == 0)
            return ;
        mlx_ptr = mlx_init();
        mlx_win = mlx_new_window(mlx_ptr, 2550, 1380, "FDF");
        img.img = mlx_new_image(mlx_ptr, 2550, 1380);
        img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
                                    &img.endian);
        calc_zoom(&mlx.zoom, dimensions.horizontal);
        draw(&img, map, dimensions, mlx);
        mlx_put_image_to_window(mlx_ptr, mlx_win, img.img, 0, 0); 
        mlx_loop(mlx_ptr);
}
int main(int ac, char **av)
{
    if (ac == 2)
    {
        fdf(av[1]);
    }
    else
        write(1, "\e[1;31mERROR: Bad arguments\e[0m", 27);
    return (0);
}
