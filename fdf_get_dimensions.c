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

	if (!str && !dimensions.horizontal)
		return (0);
	trim_space = ft_strtrim(str, " ");
	trim_space_nl = ft_strtrim(str, " \n");
	if (trim_space[0] == '\n')
	{
		if (trim_space)
			free(trim_space);
		if (trim_space_nl)
			free(trim_space_nl);
		return (1);
	}
	else if (dimensions.horizontal != 0 && \
			dimensions.horizontal != get_len(trim_space_nl))
	{
		if (trim_space)
			free(trim_space);
		if (trim_space_nl)
			free(trim_space_nl);
		return (1);
	}
	return (0);
}

int	get_x_y_len(int fd, t_dimensions **dimensions)
{
	char	*str;
	char	*to_free;

	(**dimensions).vertical = 0;
	while (1)
	{
		str = NULL;
		to_free = NULL;
		to_free = get_next_line(fd);
		if (to_free && check_map(to_free, **dimensions))
			return (1);
		if (!to_free)
			break ;
		str = ft_strtrim(to_free, " \n");
		if (to_free)
			free(to_free);
		if ((**dimensions).horizontal == 0)
			(**dimensions).horizontal = get_len(str);
		free(str);
		(**dimensions).vertical++;
	}
	if (!(**dimensions).vertical)
		return (1);
	return (0);
}
