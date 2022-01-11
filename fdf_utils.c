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
/* ************************************************************************** */
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
                child[1] = 0xFFFFFF;
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
static void get_map(int fd,int ***map, t_data **dimensions)
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
/* ************************************************************************** */
int ***get_map_from_fd(char *file_name, t_data *dimensions)
{
    int ***map;
    int fd;
    
    map = 0;
    fd = 0;
    fd = open(file_name, O_RDONLY);
    dimensions->vertical = get_y_len(fd);
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
