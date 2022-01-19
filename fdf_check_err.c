#include "fdf.h"

void err(int err, t_dimensions **dimensions)
{
    if(err == 1)
        write(1, "\e[1;31mERROR: Invalid map\e[0m", 30);
    else if (2)
        write(1, "\e[1;31mERROR: allocation failed\e[0m", 35);
    (**dimensions).horizontal = 0;
    (**dimensions).vertical = 0;
}

void free_3d_arr(int ***map, t_dimensions dimensions)
{
    int i;
    int j;

    i = 0;
    if (map)
    {
        while(i < dimensions.vertical)
        {
            if (map[i])
            {
                j = 0;
                while(j < dimensions.horizontal)
                {
                    if(map[i][j])
                        free(map[i][j]);
                    j++;
                }
                free(map[i]);
            }
            i++;
        }
        free(map);
    }
}





// void alloc_err(int ***map, t_dimensions **dimensions)
// {
//     int i;
//     int j;

//     i = 0;
    
//     while(i < (**dimensions).vertical)
//     {
//         j = 0;
//         while(j < (**dimensions).horizontal)
//         {
//             if(**map)
//                 free(**map++);
//             j++;
//         }
//         if (*map)
//             free(*map++);
//         i++;
//     }
//     if(map)
//         free(map);
//     (**dimensions).vertical = 0;
//     (**dimensions).horizontal = 0;
// }