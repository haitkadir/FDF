#include "fdf.h"

void drawline(void *mlx, void *mlx_win,int color , int x0, int y0, int x1, int y1)
{
    int dx, sx,dy,sy,err,e2;

    dx =  abs(x1-x0);
    sx = x0<x1 ? 1 : -1;
    dy = -abs(y1-y0);
    sy = y0<y1 ? 1 : -1;
    err = dx+dy;  /* error value e_xy */
    while (1)
    {  /* loop */
        // plot(x0, y0);
        mlx_pixel_put(mlx, mlx_win, x0, y0, color);
        if (x0 == x1 && y0 == y1)
            break;
        e2 = 2*err;
        if (e2 >= dy)
        { /* e_xy+e_x > 0 */
            err += dy;
            x0 += sx;
        }
        if (e2 <= dx)
        { /* e_xy+e_y < 0 */
            err += dx;
            y0 += sy;
        }
    }
}

static int get_y_len(int fd)
{
    char *str;
    int i;

    i = 0;
    str = 0;
    while(1)
    {
        str = get_next_line(fd);
        if(!str)
            break;
        else
            free(str);
        i++;
    }
    return(i);
}
int **get_map_from_fd(char *file_name, t_data *dimensions)
{
    int **map;
    int *map_child;
    char **splited;
    char *str;
    int fd;
    int i,j;
    
    map = 0;
    map_child = 0;
    splited = 0;
    str = 0;
    fd = 0;

    fd = open(file_name, O_RDONLY);
    dimensions->vertical = get_y_len(fd);
    map = (int **)ft_calloc(dimensions->vertical + 1, sizeof(int *));
    if(!map)
        return (0);
    close(fd);
    fd = 0;
    fd = open(file_name, O_RDONLY);
    i = 0;
    while(1)
    {
        str = get_next_line(fd);
        if(!str)
            break;
        splited = ft_split(str, ' ');
        free(str);
        str = 0;
        j = 0;
        while (splited[j])
            j++;
        if(dimensions->horizontal == 0)
            dimensions->horizontal = j;
        map_child = (int *)ft_calloc(j + 1, sizeof(int));
        j = 0;
        while(splited[j])
        {
            map_child[j] = ft_atoi(splited[j]);
            j++;
        }
        free(splited);
        splited = 0;
        map[i] = map_child;
        map_child = 0;
        i++;
    }
    close(fd);

    // sp = ft_split(get_next_line(fd), ' ');

    return (map);
}