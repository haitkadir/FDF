/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haitkadi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 16:57:23 by haitkadi          #+#    #+#             */
/*   Updated: 2022/01/11 16:57:36 by haitkadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void check_err(int err, t_dimensions **dimensions)
{
    if(err == 1)
        write(1, "\e[1;31mERROR: Envalid map\e[0m", 30);
    (**dimensions).horizontal = 0;
    (**dimensions).vertical = 0;
}

static int ft_ishexa(int c){
    return((c >= '0' && c <= '9')
        || (c >= 'A' && c <= 'F')
        || (c >= 'a' && c <= 'f'));
}

int ft_htoi(char *hexa){
    int i;
    int result;
    int to_convert;
    int len;

    result = 0;
    to_convert = 0;
    i = 0;
    if (hexa[0] == '0' && (ft_toupper(hexa[1]) == 'X'))
    {
        i += 2;
        len = 2;
        while(ft_ishexa(hexa[len]))
            len++;
        while(ft_ishexa(hexa[i]))
        {
            if(ft_toupper(hexa[i]) >= 'A' && ft_toupper(hexa[i]) <= 'F')
                to_convert = (ft_toupper(hexa[i]) - 55);
            else if(ft_isdigit(hexa[i]))
                to_convert = (hexa[i] - 48);
    	    result +=(to_convert * pow(16, (len--) - 3));
    	    i++;
    	}
    	return(result);
    }
    return (0);
}

/* ************************************************************************** */

static void    iso_pro(int *x, int *y, int z)
{
    int x_tmp;
    int y_tmp;

    x_tmp = *x;
    y_tmp = *y;
    *x = (x_tmp - y_tmp ) * cos(0.523599);
    *y = - z + (x_tmp + y_tmp) * sin(0.523599);
}

void drawline(t_data **img, t_mlx mlx, int x0, int y0, int x1, int y1, int ***map)
{
    int dx, sx,dy,sy,err,e2;
    int z;
    int z1;

    z = map[y0][x0][0];
    z1 = map[y1][x1][0];

    x0 *= mlx.zoom;
    y0 *= mlx.zoom;
    x1 *= mlx.zoom;
    y1 *= mlx.zoom;
    if (z != 0)
        z *= 1;
    if (z1 != 0)
        z1 *= 1;

    iso_pro(&x0, &y0, z);
    iso_pro(&x1, &y1, z1);
    dx =  abs(x1-x0);
    sx = x0<x1 ? 1 : -1;// ternary 
    dy = -abs(y1-y0);
    sy = y0<y1 ? 1 : -1;// ternary 
    err = dx+dy;  /* error value e_xy */

    while (1)
    {
        my_mlx_pixel_put(&**img, x0 + 1200, y0 + 200, mlx.color);
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

/* ************************************************************************** */

static int get_x_y_len(int fd, t_dimensions **dimensions)
{
    char *str;
    char *to_free;
    int i;
    int len;
    int index;

    index = 0;
    while(1)
    {
        i = 0;
        len = 1;
        str = 0;
        to_free = NULL;
        to_free = get_next_line(fd);
        str = ft_strtrim(to_free, " \n");
        free(to_free);
        if(!str)
            break;
        while(str[i])
            if(str[i++] == ' ' && str[i] != ' ')
                len++;
        if((**dimensions).horizontal == 0)
            (**dimensions).horizontal = len;
        else if ((**dimensions).horizontal != len)
            return(1);
        free(str);
        index++;
    }
    if(!index)
        return (1);
    (**dimensions).vertical = index;
    return (0);
}

/* ************************************************************************** */

static int **get_map_child_util(int **map_child, char *str)
{
    int *child;
    int i;
    int j;

    i = 0;
    j = 0;
    child = NULL;
    while(str[i])
        if(str[i] == ' ')
            i++;
        else
        {
            child = (int *)ft_calloc(2, sizeof(int));
            child[0] = ft_atoi(&str[i]);
            while((str[i] && str[i] != ' ') && (str[i] && str[i] != ','))
                i++;
            if(str[i] == ',')
                child[1] = ft_htoi(&str[++i]);
            else
                child[1] = (21000 * (child[0] + 1 * 400));
            while(str[i] && (str[i] != ' '))
                i++;
            map_child[j++] = child;
        }
    return (map_child);
}

/* ************************************************************************** */

static int **get_map_child(char *str, int len)
{
    int **map_child;

    map_child = (int **)ft_calloc(len + 1, sizeof(int *));
    return(get_map_child_util(map_child, str));
}

/* ************************************************************************** */

static void get_map(int fd,int ***map, t_dimensions **dimensions) // more than 25 lines in function
{
    char *str;
    char *to_free;
    int n;

    n = 0;
    while(1)
    {
        str = NULL;
        to_free = get_next_line(fd);
        str = ft_strtrim(to_free, " \n");
        free(to_free);
        to_free = NULL;
        if(!str)
            break;
        map[n++] = get_map_child(str, (**dimensions).horizontal);
        if(str)
            free(str);
    }
}
/* ************************************************************************** */
int ***get_map_from_fd(char *file_name, t_dimensions *dimensions)
{
    int ***map;
    int fd;
    int err;
    
    map = 0;
    fd = 0;
    fd = open(file_name, O_RDONLY);
    err = get_x_y_len(fd, &dimensions);
    if(fd == -1 || err)
    {
        check_err(1, &dimensions);
        return (0);
    }
    map = (int ***)ft_calloc(dimensions->vertical + 1, sizeof(int **));
    if(!map)
        return (0);
    close(fd);
    fd = 0;
    fd = open(file_name, O_RDONLY);
    get_map(fd, map, &dimensions);
    close(fd);
    return (map);
}
