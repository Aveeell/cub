/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoch <mkoch@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 13:04:44 by mkoch             #+#    #+#             */
/*   Updated: 2022/07/08 16:01:40 by mkoch            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static int	check_struct(t_all *all, char *str)
{
	if (str)
		error(all, 0);
	return (1);
}

static void	check_value_of_color(int j, int *arr, t_all *all)
{
	while (j--)
		if (arr[j] > 255 || arr[j] < 0)
			error(all, 0);
}

static void	check_color(t_all *all, char *str, int *arr)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (str[i])
	{
		while (str[i] == ' ')
			i++;
		if (str[i] < '0' || str[i] > '9')
			error(all, 0);
		else
		{
			arr[j] = ft_atoi(&str[i]);
			while (str[i] >= '0' && str[i] <= '9')
				i++;
			if (str[i] == ',')
			i++;
		}
		j++;
	}
	if (j != 3 || str[ft_strlen(str) - 1] == ',')
		error(all, 0);
	check_value_of_color(j, arr, all);
}

static void	write_tex_into_struct(char *str, t_all *all, t_tex *tex)
{
	if (!ft_strncmp(str, "NO ", 3) && check_struct(all, tex->no))
		tex->no = ft_strdup(str, 0);
	else if (!ft_strncmp(str, "SO ", 3) && check_struct(all, tex->so))
		tex->so = ft_strdup(str, 0);
	else if (!ft_strncmp(str, "WE ", 3) && check_struct(all, tex->we))
		tex->we = ft_strdup(str, 0);
	else if (!ft_strncmp(str, "EA ", 3) && check_struct(all, tex->ea))
		tex->ea = ft_strdup(str, 0);
	else if (!ft_strncmp(str, "F ", 2) && check_struct(all, tex->fl))
		tex->fl = ft_strdup(str, 0);
	else if (!ft_strncmp(str, "C ", 2) && check_struct(all, tex->ceil))
		tex->ceil = ft_strdup(str, 0);
	else
	{
		free(str);
		error(all, 0);
	}
}

void	get_struct_textures(t_all *all, char **tex_raw, t_tex *tex)
{
	int		i;
	char	*str;

	i = 0;
	while (tex_raw[i])
	{
		str = ft_strtrim(tex_raw[i], " ");
		write_tex_into_struct(str, all, tex);
		i++;
		free(str);
	}
	if (!tex->no || !tex->so || !tex->we || !tex->ea || !tex->fl || \
		!tex->ceil)
		error(all, 0);
	check_color(all, tex->fl, tex->fl_rgb);
	check_color(all, tex->ceil, tex->cl_rgb);
}
