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
    { 
        mlx_pixel_put(mlx, mlx_win, x0, y0, color);
        if (x0 == x1 && y0 == y1)
            break;
        e2 = 2 * err;
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
        free(str);
        i++;
    }
    return(i);
}

static int *get_map_child(char *str, int len)
{
    int *map_child;
    int i;
    int j;

    i = 0;
    j = 0;
    map_child = NULL;
    map_child = (int *)ft_calloc(len + 1, sizeof(int));
    while(str[i])
    {
        if(str[i] == ' '){
            i++;
            continue;
        }
        else{
            map_child[j++] = ft_atoi(&str[i]);
            
            while(str[i] && str[i] != ' ')
                i++;
            continue;
        }
    }
    return(map_child);
}

static void get_map(int fd,int **map, t_data **dimensions)
{
    char *str;
    int i;
    int n;
    int len;

    i = 0;
    len = 0;
    n = 0;
    while(1)
    {
        str = NULL;
        str = get_next_line(fd);
        if(!str)
            break;
        while(str[i])
            if(str[i++] == ' ' && str[i] != ' ')
                len++;
        if((**dimensions).horizontal == 0)
            (**dimensions).horizontal = len;
        map[n++] = get_map_child(str, len);
        if(str)
            free(str);
    }
}

int **get_map_from_fd(char *file_name, t_data *dimensions)
{
    int **map;
    int fd;
    
    map = 0;
    fd = 0;
    fd = open(file_name, O_RDONLY);
    dimensions->vertical = get_y_len(fd);
    map = (int **)ft_calloc(dimensions->vertical + 1, sizeof(int *));
    if(!map)
        return (0);
    close(fd);
    fd = 0;
    fd = open(file_name, O_RDONLY);
    get_map(fd, map, &dimensions);
    close(fd);
    return (map);
}
