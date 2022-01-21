/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+::+:          :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haitkadi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 21:52:23 by haitkadi          #+#    #+#             */
/*   Updated: 2021/11/22 21:52:26 by haitkadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*ptr;
	size_t	i;

	ptr = NULL;
	ptr = (char *)malloc(count * size);
	if (!ptr)
		return (NULL);
	i = 0;
	while (i < count * size)
	{
		ptr[i] = 0;
		i++;
	}
	return ((void *)ptr);
}

char	*ft_strchr(const char *s, int c)
{	
	int		i;
	char	*str;
	char	ch;

	if (!s)
		return (0);
	str = (char *)s;
	ch = (char)c;
	i = 0;
	while (str[i] && str[i] != ch)
		i++;
	if (str[i] == ch)
		return (str + i);
	else
		return (0);
}

char	*ft_strdup(const char *s1)
{
	char	*ptr;
	int		i;

	i = 0;
	ptr = (char *)malloc(sizeof(char) * ft_strlen(s1) + 1);
	if (!ptr)
		return (0);
	while (s1[i])
	{
		ptr[i] = s1[i];
		i++;
	}
	ptr[i] = 0;
	return (ptr);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	int		str_size;
	char	*new_str;

	if (!s1)
		return (0);
	str_size = (ft_strlen(s1) + ft_strlen(s2));
	new_str = (char *)malloc(sizeof(char) * str_size + 1);
	if (!new_str)
		return (0);
	i = 0;
	while (s1[i])
	{
		new_str[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
		new_str[i++] = s2[j++];
	new_str[i] = 0;
	return (new_str);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
	{
		i++;
	}
	return (i);
}
