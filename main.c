#include "fdf.h"

void print(int ***map, t_dimensions dimensions){
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

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

    if(x < 2550 && y < 1380)
    {
	    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	    *(unsigned int*)dst = color;
    }
}


static void draw(t_data *img, int ***map, t_dimensions dimensions, t_mlx mlx)
{
    int x;
    int y;
    int color;

    y = 0;
    while(y < dimensions.vertical)
    {
        x = 0;
        while(x < dimensions.horizontal)
        {
            if(x < dimensions.horizontal - 1)
            {
                mlx.color = map[y][x][1];
                if(map[y][x + 1][1] != mlx.color && map[y][x + 1][0] != 0)
                    mlx.color = map[y][x + 1][1];
                drawline(&img, mlx, x , y , (x + 1), y , map);
            }
            if (y < dimensions.vertical - 1)
            {
                mlx.color = map[y][x][1];
                if(map[y + 1][x][1] != mlx.color && map[y + 1][x][0] != 0)
                    mlx.color = map[y + 1][x][1];
                drawline(&img, mlx, x , y , x , (y + 1) , map);
            }
            x++;
        }
        y++;
    }
}

int main(int ac, char **av)
{
    t_dimensions  dimensions;
    t_mlx mlx;
    int vitagors;

	void	*mlx_ptr;
	void	*mlx_win;
	t_data	img;

    vitagors = 0;
    ft_bzero(&dimensions, sizeof(t_dimensions));
    int ***map = get_map_from_fd(av[1], &dimensions);
    if(dimensions.horizontal == 0 && dimensions.vertical == 0)
        return(0);
	mlx_ptr = mlx_init();
	mlx_win = mlx_new_window(mlx_ptr, 2550, 1380, "FDF");
	img.img = mlx_new_image(mlx_ptr, 2550, 1380);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
    vitagors = sqrt(pow(dimensions.horizontal, 2) + pow(dimensions.vertical, 2));
    // printf("%d", vitagors);
    if (dimensions.horizontal > 400)
        mlx.zoom = 2;
    if(dimensions.vertical < 300)
        mlx.zoom = 5;
    if (dimensions.horizontal < 100)
        mlx.zoom = 20;

    draw(&img, map, dimensions, mlx);
	mlx_put_image_to_window(mlx_ptr, mlx_win, img.img, 0, 0); 
	mlx_loop(mlx_ptr);
}
































// int main(int ac, char **av)
// {
//     t_dimensions  dimensions;
//     t_mlx mlx;

//     ft_bzero(&dimensions, sizeof(t_dimensions));
//     int ***map = get_map_from_fd(av[1], &dimensions);
//     int x = 0;
//     int y;
//     printf("%d\n", dimensions.horizontal);
//     printf("%d\n", dimensions.vertical);
//     mlx.zoom = 20;
//     mlx.win_w = 2560;
//     mlx.win_h = 1390;
//     mlx.mlx = mlx_init();
//     mlx.mlx_win = mlx_new_window(mlx.mlx, mlx.win_w, mlx.win_h, "FDF");
//     draw(map, &dimensions, &mlx);
//     mlx_loop (mlx.mlx);
// }
