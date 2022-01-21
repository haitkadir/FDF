/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_htoi.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haitkadi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 22:02:04 by haitkadi          #+#    #+#             */
/*   Updated: 2022/01/20 22:02:09 by haitkadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static	int	ft_ishexa(int c)
{
	return ((c >= '0' && c <= '9') || (c >= 'A' && c <= 'F') || \
			(c >= 'a' && c <= 'f'));
}

static	int	ft_hexalen(char *hexa)
{
	int	i;

	i = 0;
	while (ft_ishexa(hexa[i]))
		i++;
	return (i);
}

int	ft_htoi(char *hexa)
{
	int	i;
	int	result;
	int	to_convert;
	int	len;

	result = 0;
	to_convert = 0;
	i = 0;
	if (hexa[0] == '0' && (ft_toupper(hexa[1]) == 'X'))
	{
		i += 2;
		len = ft_hexalen(&hexa[i]);
		while (ft_ishexa(hexa[i]))
		{
			if (ft_toupper(hexa[i]) >= 'A' && ft_toupper(hexa[i]) <= 'F')
				to_convert = (ft_toupper(hexa[i]) - 55);
			else if (ft_isdigit(hexa[i]))
				to_convert = (hexa[i] - 48);
			result += (to_convert * pow(16, (len--) - 1));
			i++;
		}
		return (result);
	}
	return (0);
}
