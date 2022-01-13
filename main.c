#include "fdf.h"


void print(int ***map, t_data dimensions){
    int x;
    int y;

    y = 0;
    while(y < dimensions.vertical){
        x = 0;
        while(x < dimensions.horizontal){
            printf("%d ", map[y][x][0]);
            x++;
        }
        printf("\n");
        y++;
    }
}
static void draw(int ***map, t_data *dimensions, t_mlx *mlx)
{
    int x;
    int y;
    int color;

    y = 0;
    while(y < dimensions->vertical)
    {
        x = 0;
        while(x < dimensions->horizontal)
        {
            mlx->color = map[y][x][1];
            if(x < dimensions->horizontal - 1)
                drawline(mlx, x , y , (x + 1), y , map);
            if (y < dimensions->vertical - 1)
                drawline(mlx, x , y , x , (y + 1) , map);
            x++;
        }
        y++;
    }
}

int main(int ac, char **av)
{
    t_data  dimensions;
    t_mlx mlx;

    ft_bzero(&dimensions, sizeof(t_data));
    int ***map = get_map_from_fd(av[1], &dimensions);
    //print(map,dimensions);
    int x = 0;
    int y;
    printf("%d\n", dimensions.horizontal);
    printf("%d\n", dimensions.vertical);

    mlx.zoom = 20;
    mlx.win_w = 2560;
    mlx.win_h = 1390;
    mlx.mlx = mlx_init();
    mlx.mlx_win = mlx_new_window(mlx.mlx, mlx.win_w, mlx.win_h, "FDF");
    draw(map, &dimensions, &mlx);
    mlx_loop (mlx.mlx);
}
