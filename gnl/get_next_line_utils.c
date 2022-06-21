/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jerrok <jerrok@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 10:38:02 by jerrok            #+#    #+#             */
/*   Updated: 2022/06/20 11:27:19 by jerrok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen(char const *str)
{
	int	i;

	i = 0;
	if (str)
	{
		while (str[i] != '\0')
			i++;
	}
	return (i);
}

char	*ft_strdup(char *src, int flag)
{
	char	*str;
	int		i;

	i = 0;
	if (!src)
		return (NULL);
	str = malloc(sizeof(char) * ft_strlen(src) + 1 + flag);
	if (!str)
		return (NULL);
	while (src[i] != '\0')
	{
		str[i] = src[i];
		i++;
	}
	if (flag)
	{
		str[i] = '\n';
		free(src);
	}
	str[i + flag] = '\0';
	return (str);
}

char	*ft_strchr(char const *str, int n)
{
	unsigned char	*s;
	size_t			i;

	i = 0;
	s = (unsigned char *)str;
	if (!s)
		return (NULL);
	while (s[i] != '\0')
	{
		if (s[i] == (unsigned char)n)
			return ((char *)&s[i]);
		i++;
	}
	if (s[i] == (unsigned char)n)
		return ((char *)&s[i]);
	return (NULL);
}

size_t	ft_strcpy(char *dest, char const *src)
{
	size_t	i;

	i = 0;
	if (!dest)
		return (0);
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (i);
}
