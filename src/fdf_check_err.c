/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_check_err.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haitkadi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 17:38:40 by haitkadi          #+#    #+#             */
/*   Updated: 2022/01/20 17:38:43 by haitkadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	err(int err, t_dimensions **dimensions)
{
	if (err == 1)
		write(1, "\e[1;31mERROR: Invalid map\e[0m", 30);
	else if (2)
		write(1, "\e[1;31mERROR: allocation failed\e[0m", 35);
	(**dimensions).horizontal = 0;
	(**dimensions).vertical = 0;
}

void	free_3d_arr(int ***map, t_dimensions dimensions)
{
	int	i;
	int	j;

	i = 0;
	if (map)
	{
		while (i < dimensions.vertical)
		{
			if (map[i])
			{
				j = 0;
				while (j < dimensions.horizontal)
				{
					if (map[i][j])
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
