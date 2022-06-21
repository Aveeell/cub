/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jerrok <jerrok@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 12:25:56 by jerrok            #+#    #+#             */
/*   Updated: 2022/06/20 14:40:13 by jerrok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static int	ft_count_word(char const *s, char c)
{
	int	i;
	int	word;

	i = 0;
	word = 0;
	if (!s || s[0] == '\0')
		return (0);
	while (s[i] != '\0')
	{
		if (s[i] != c && s[i - 1] == c)
			word++;
		if (s[i - 1] == '1' && (s[i] == c && s[i + 1] == c))
		{
			if (s[i - 2] != ',' && s[i - 3] != ',' && s[i - 4] != ',')
				return (-1);
		}
		i++;
	}
	return (word + 1);
}

static int	ft_len_word(char const *s, char c, int i)
{
	int	len;

	len = 0;
	while (s[i] == c && s[i] != '\0')
		i++;
	while (s[i] != c && s[i] != '\0')
	{
		len++;
		i++;
	}
	return (len);
}

static char	**ft_free(char **res, int i)
{
	int	j;

	j = 0;
	while (i > j && res[j] != 0)
	{
		free(res[j]);
		j++;
	}
	free(res);
	return ((void *)0);
}

int	ft_write_str(char *res, char const *s, char c, int j)
{
	int	i;

	i = 0;
	while (s[j] != c && s[j] != '\0')
	{
		res[i] = s[j];
		j++;
		i++;
	}
	res[i] = '\0';
	return (j);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	char	**res;

	i = 0;
	j = 0;
	if (!s || ft_count_word(s, c) == -1)
		return ((void *)0);
	res = malloc(sizeof(char *) * (ft_count_word(s, c) + 1));
	if (!res)
		return ((void *)0);
	while (i < ft_count_word(s, c))
	{
		res[i] = malloc(sizeof(char) * (ft_len_word(s, c, j) + 1));
		if (!res[i])
			return (ft_free(res, i));
		while (s[j] == c)
			j++;
		j = ft_write_str(res[i], s, c, j);
		i++;
	}
	res[i] = ((void *)0);
	free((char *)s);
	return (res);
}
