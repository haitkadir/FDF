/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+::+:          :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haitkadi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 21:37:16 by haitkadi          #+#    #+#             */
/*   Updated: 2021/11/22 21:37:21 by haitkadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

static	void	iter_file_output(char **line, \
	char **buf, int *ret, int fd)
{
	char	*temp;

	while (!ft_strchr(*line, '\n'))
	{
		*ret = read(fd, *buf, BUFFER_SIZE);
		if (*ret <= 0)
			break ;
		else
		{
			if (*line)
			{
				temp = *line;
				*line = ft_strjoin(*line, *buf);
				free(temp);
				if (!*line)
					return ;
			}
			else
				*line = ft_strdup(*buf);
			ft_bzero(*buf, BUFFER_SIZE);
		}
	}
}

static	void	the_recipe(char **the_rest, char **line)
{
	char	*temp;
	char	*ptr_to_nl;

	ptr_to_nl = NULL;
	if (ft_strchr(*line, '\n'))
		ptr_to_nl = ft_strchr(*line, '\n');
	temp = 0;
	if (ptr_to_nl && *(ptr_to_nl + 1))
	{
		temp = *line;
		*line = 0;
		*the_rest = ft_strdup(ft_strchr(temp, '\n') + 1);
		if (!*the_rest)
			return ;
		ft_bzero(ft_strchr(temp, '\n') + 1, \
			ft_strlen((ft_strchr(temp, '\n') + 1)));
		*line = ft_strdup(temp);
		free(temp);
		if (!*line)
			return ;
	}
}

char	*get_next_line(int fd)
{
	char		*buf;
	char		*line;
	static char	*the_rest;
	int			ret;

	line = NULL;
	buf = (char *)ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buf)
		return (0);
	if (fd >= 0)
	{
		if (the_rest)
		{
			line = ft_strdup(the_rest);
			if (!line)
				return (0);
			free(the_rest);
			the_rest = 0;
		}
		iter_file_output(&line, &buf, &ret, fd);
		the_recipe(&the_rest, &line);
	}
	free(buf);
	return (line);
}
