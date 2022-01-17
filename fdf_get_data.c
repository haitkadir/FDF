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

static int ft_hexalen(char *hexa)
{
    int i;

    i = 0;
    while(ft_ishexa(hexa[i]))
        i++;
    return (i);
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
        len = ft_hexalen(&hexa[i]);
        while(ft_ishexa(hexa[i]))
        {
            if(ft_toupper(hexa[i]) >= 'A' && ft_toupper(hexa[i]) <= 'F')
                to_convert = (ft_toupper(hexa[i]) - 55);
            else if(ft_isdigit(hexa[i]))
                to_convert = (hexa[i] - 48);
    	    result += (to_convert * pow(16, (len--) -1));
    	    i++;
    	}
    	return(result);
    }
    return (0);
}



/* ************************************************************************** */
static int get_len(char *str)
{
    int i;
    int len;

    i = 0;
    len = 1;
    while(str[i])
        if(str[i++] == ' ' && str[i] != ' ')
            len++;
    return(len);
}
static int get_x_y_len(int fd, t_dimensions **dimensions)
{
    char *str;
    char *to_free;
    int len;
    int index;

    index = 0;
    while(1)
    {
        str = NULL;
        to_free = NULL;
        to_free = get_next_line(fd);
        str = ft_strtrim(to_free, " \n");
        free(to_free);
        if(!str)
            break;
        len = get_len(str);
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

static void get_map_child_util(int **map_child, char *str)
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
            if(str[i] == ',' && str[i + 1] != ' ' && str[i + 1] != 0)
                child[1] = ft_htoi(&str[++i]);
            else
                child[1] = (21000 * (child[0] + 1 * 400));
            while(str[i] && (str[i] != ' '))
                i++;
            map_child[j++] = child;
        }
}

/* ************************************************************************** */

static int **get_map_child(char *str, int len)
{
    int **map_child;

    map_child = (int **)ft_calloc(len + 1, sizeof(int *));
    get_map_child_util(map_child, str);
    return(map_child);
}

/* ************************************************************************** */

static void get_map(int fd,int ***map, t_dimensions **dimensions)
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
        if (to_free)
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
