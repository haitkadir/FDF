#include "fdf.h"

static void initial_data_x(t_mlx *mlx, int x, int y)
{
    mlx->x0 = x;
    mlx->y0 = y;
    mlx->x1 = x + 1;
    mlx->y1 = y;
}
static void initial_data_y(t_mlx *mlx, int x, int y)
{
    mlx->x0 = x;
    mlx->y0 = y;
    mlx->x1 = x;
    mlx->y1 = y + 1;
}
static void calc_color1(int *color, int y, int x, int ***map)
{
    *color = map[y][x][1];
    if(map[y][x + 1][1] != *color && map[y][x + 1][0] != 0)
        *color = map[y][x + 1][1];
}
static void calc_color2(int *color, int y, int x, int ***map)
{
    *color = map[y][x][1];
    if(map[y + 1][x][1] != *color && map[y + 1][x][0] != 0)
        *color = map[y + 1][x][1];
}
void draw(t_data *img, int ***map, t_dimensions dimensions, t_mlx mlx)
{
    int x;
    int y;

    y = 0;
    while(y < dimensions.vertical)
    {
        x = 0;
        while(x < dimensions.horizontal)
        {
            if(x < dimensions.horizontal - 1)
            {
                calc_color1(&mlx.color, y, x, map);
                initial_data_x(&mlx, x, y);
                drawline(&img, mlx, map);
            }
            if (y < dimensions.vertical - 1)
            {
                calc_color2(&mlx.color, y, x, map);
                initial_data_y(&mlx, x, y);
                drawline(&img, mlx, map);
            }
            x++;
        }
        y++;
    }
}
