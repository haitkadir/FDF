#include "fdf.h"

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

int get_x_y_len(int fd, t_dimensions **dimensions)
{
    char *str;
    char *to_free;

    (**dimensions).vertical = 0;
    while(1)
    {
        str = NULL;
        to_free = NULL;
        to_free = get_next_line(fd);
        str = ft_strtrim(to_free, " \n");
        if(to_free)
            free(to_free);
        if(!str || !ft_isdigit(str[0]))
            break;
        if((**dimensions).horizontal == 0)
            (**dimensions).horizontal = get_len(str);
        else if ((**dimensions).horizontal != get_len(str))
            return(1);
        free(str);
        (**dimensions).vertical++;
    }
    if(!(**dimensions).vertical)
        return (1);
    return (0);
}