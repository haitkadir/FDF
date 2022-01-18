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


/* ************************************************************************** */


/* ************************************************************************** */

static int get_map_child_util(int **map_child, char *str)
{
    int *child;
    int i;

    i = 0;
    child = NULL;
    while(str[i])
        if(str[i] == ' ')
            i++;
        else
        {
            child = (int *)ft_calloc(2, sizeof(int));
            if(!child)
                return (-1);
            child[0] = ft_atoi(&str[i]);
            while((str[i] && str[i] != ' ') && (str[i] && str[i] != ','))
                i++;
            if(str[i] == ',' && str[i + 1] != ' ' && str[i + 1] != 0)
                child[1] = ft_htoi(&str[++i]);
            else
                child[1] = (21000 * (child[0] + 1 * 400));
            while(str[i] && (str[i] != ' '))
                i++;
            *map_child++ = child;
        }
        return (0);
}

/* ************************************************************************** */

static int **get_map_child(char *str, int len)
{
    int **map_child;

    map_child = NULL;
    map_child = (int **)ft_calloc(len + 1, sizeof(int *));
    if (!map_child)
        return (-1);
    if(get_map_child_util(map_child, str) == -1)
        return (-1);
    return(map_child);
}

/* ************************************************************************** */

static void get_map(int fd,int ***map, t_dimensions **dimensions)
{
    char *str;
    char *to_free;
    int **map_child;

    map_child = NULL;
    while(1)
    {
        str = NULL;
        to_free = get_next_line(fd);
        str = ft_strtrim(to_free, " \n");
        if (to_free)
            free(to_free);
        to_free = NULL;
        if(!str)
            break;
        map_child = get_map_child(str, (**dimensions).horizontal);
        if (map_child == -1)
            return (-1);
        *map++ = map_child;
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
