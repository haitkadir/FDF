#include "fdf.h"
// // #include "get_next_line.h"

// void    background(void *mlx, void *mlx_win, int width, int height)
// {

//     for (int x = 0; x < width; x++)
//         for (int y = 0; y < height; y++)
//         {
//             mlx_pixel_put(mlx, mlx_win, x, y, 9206502);
//         }
// }
// void    letter_line(void *mlx, void *mlx_win, int width, int height)
// {
//     for (int x = 50; x < 700; x += width)
//         for (int y = 50; y < 700; y += height)
//         {
//             mlx_pixel_put(mlx, mlx_win, x, y, 16119546);
//         }
// }

int main(int ac, char **av)
{
    t_data  dimensions;

    ft_bzero(&dimensions, sizeof(t_data));
    int **map = get_map_from_fd(av[1], &dimensions);
    int **map2 = get_map_from_fd(av[1], &dimensions);
    int i,j;
    int x;
    int y = 0;
    int color = 16538725;

    void *mlx;
    void *mlx_win;
    int width = 1920;
    int height = 1080;

    mlx = mlx_init();
    mlx_win = mlx_new_window(mlx, width, height, "FDF");

    while(x < dimensions.horizontal)
    {
        y = 0;
        while(y < dimensions.vertical)
        {
            color = 16538725;
            // if (map[y][x] == 0)
            //     color = 3696598;
            if(x < dimensions.horizontal - 1)
                drawline(mlx, mlx_win, color, x * 3, y * 3, (x + 1) * 3, y * 3);
            if (y < dimensions.vertical - 1)
                drawline(mlx, mlx_win, color, x * 3, y * 3, x * 3, (y + 1) * 3);

            y++;
        }
        x++;
    }
    mlx_loop (mlx);

}