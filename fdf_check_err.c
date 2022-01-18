#include "fdf.h"

void check_err(int err, t_dimensions **dimensions)
{
    if(err == 1)
        write(1, "\e[1;31mERROR: Invalid map\e[0m", 30);
    (**dimensions).horizontal = 0;
    (**dimensions).vertical = 0;
}

void alloc_err(int ***map, t_dimensions dimensions)
{
    int i;
    int j;

    i = 0;
    while(i < dimensions.vertical)
    {
        j = 0;
        while(j < dimensions.horizontal)
        {
            if(map[i][j])
                free(map[i][j]);
            j++;
        }
        if (map[i])
            free(map[i]);
        i++;
    }
    if(map)
        free(map);
}