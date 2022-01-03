#ifndef FDF_H
# define FDF_H
#include "mlx.h"
#include <math.h>
#include <stdio.h>
#include <fcntl.h>
#include "./get_next_line/get_next_line.h"
#include "./libft/libft.h"
// get data
typedef struct t_data
{
    int horizontal;
    int vertical;
}   t_data;

// functions
int **get_map_from_fd(char *, t_data *);
void drawline(void *, void *, int, int, int, int, int);
#endif