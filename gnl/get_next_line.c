/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jerrok <jerrok@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 10:38:02 by jerrok            #+#    #+#             */
/*   Updated: 2022/06/20 11:29:05 by jerrok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_join(char *res, char *s, size_t len)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		res[len + i] = s[i];
		i++;
	}
	res[len + i] = '\0';
	return (res);
}

static char	*ft_strjoinn(char *s1, char *s2)
{
	char	*res;
	int		i;
	int		j;
	size_t	len_strs;

	i = 0;
	j = 0;
	if (!ft_strlen(s1))
		res = ft_strdup(s2, 0);
	else
	{
		len_strs = ft_strlen(s1) + ft_strlen(s2);
		res = malloc((sizeof(char) * len_strs + 1));
		if (!res)
			return ((void *)0);
		res = ft_join(ft_join(res, s1, 0), s2, ft_strlen(s1));
	}
	free(s1);
	return (res);
}

static char	*check_next_line(char *mod, char *ptr)
{
	char	*print_str;

	print_str = NULL;
	if (mod)
	{
		if (!mod[0])
		{
			free(mod);
			return (NULL);
		}
		ptr = ft_strchr(mod, '\n');
		if (ptr)
		{
			*ptr = '\0';
			print_str = ft_strdup(mod, 0);
			ptr++;
			ft_strcpy(mod, ptr);
		}
		else
		{	
			print_str = ft_strdup(mod, 0);
			free(mod);
		}
	}
	return (print_str);
}

static char	*check_ptr(char *ptr, char *mod, int rd)
{
	if (ptr)
	{
		*ptr = '\0';
		ptr++;
		mod = ft_strdup(ptr, 0);
	}
	if (!rd)
		return (NULL);
	return (mod);
}

char	*get_next_line(int fd)
{
	int			rd;
	char		buff[BUFFER_SIZE + 1];
	char		*ptr;
	char		*print_str;
	static char	*mod;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	ptr = ft_strchr(mod, '\n');
	print_str = check_next_line(mod, ptr);
	rd = 1;
	while (rd && !ptr)
	{
		rd = read(fd, buff, BUFFER_SIZE);
		if (rd == -1)
			break ;
		buff[rd] = '\0';
		ptr = ft_strchr(buff, '\n');
		mod = check_ptr(ptr, mod, rd);
		if (!rd)
			return (print_str);
		print_str = ft_strjoinn(print_str, buff);
	}
	return (ft_strdup(print_str, 1));
}
