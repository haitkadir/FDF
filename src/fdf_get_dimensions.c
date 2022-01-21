/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_get_dimensions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haitkadi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 21:18:52 by haitkadi          #+#    #+#             */
/*   Updated: 2022/01/20 21:19:02 by haitkadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static	int	get_len(char *str)
{
	int	i;
	int	len;

	i = 0;
	len = 1;
	while (str[i])
		if (str[i++] == ' ' && str[i] != ' ')
			len++;
	return (len);
}

static	int	check_map(char *str, t_dimensions dimensions)
{
	char	*trim_space;
	char	*trim_space_nl;
	int		error;

	error = 0;
	if (!str && !dimensions.horizontal)
		return (0);
	trim_space = ft_strtrim(str, " ");
	trim_space_nl = ft_strtrim(str, " \n");
	if (trim_space && trim_space[0] == '\n')
		error = 1;
	else if (dimensions.horizontal != 0 && \
			dimensions.horizontal != get_len(trim_space_nl))
		error = 1;
	if (trim_space)
		free(trim_space);
	if (trim_space_nl)
		free(trim_space_nl);
	return (error);
}

int	get_x_y_len(int fd, t_dimensions **dimensions)
{
	char	*str;
	char	*line;

	(**dimensions).vertical = 0;
	while (1)
	{
		str = NULL;
		line = NULL;
		line = get_next_line(fd);
		if (line && check_map(line, **dimensions))
			return (free(line), 1);
		if (!line)
			break ;
		str = ft_strtrim(line, " \n");
		if (line)
			free(line);
		if ((**dimensions).horizontal == 0)
			(**dimensions).horizontal = get_len(str);
		free(str);
		(**dimensions).vertical++;
	}
	if (!(**dimensions).vertical)
		return (1);
	return (0);
}
