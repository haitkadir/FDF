#ifndef FDF_H
# define FDF_H
#include <math.h>
#include <fcntl.h>
#include "mlx.h"
#include "./get_next_line/get_next_line.h"
#include "./libft/libft.h"
#include <stdio.h>
// get data
typedef struct t_data
{
    int horizontal;
    int vertical;
}   t_data;
// functions
int ft_htoi(char *hexa);
int ***get_map_from_fd(char *, t_data *);
void drawline(void *, void *, int, int, int, int, int);
#endif