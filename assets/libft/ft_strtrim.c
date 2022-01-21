/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haitkadi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 21:11:17 by haitkadi          #+#    #+#             */
/*   Updated: 2021/11/05 21:11:32 by haitkadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char		*result;
	size_t		i;
	size_t		j;

	i = -1;
	if (!s1 || !set)
		return (NULL);
	j = ft_strlen(s1);
	while (ft_strchr(set, s1[++i]))
		;
	while (ft_strchr(set, s1[--j]))
		;
	result = ft_substr(s1, i, j - i + 1);
	return (result);
}
