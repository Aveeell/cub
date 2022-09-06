/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_wall.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoch <mkoch@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 13:04:51 by mkoch             #+#    #+#             */
/*   Updated: 2022/07/08 16:01:56 by mkoch            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	check_with_prev_string(t_all *all, char **map, int i)
{
	int	j;
	int	k;

	if (i > 0)
	{
		j = ft_strlen(map[i]) - 1;
		k = ft_strlen(map[i - 1]) - 1;
		if (j > k)
		{
			if (map[i][k] != '1')
				error(all, 0);
			while (j > k)
			{
				if (map[i][j] != ' ' && map[i][j] != '1')
					break ;
				j--;
			}
			if (j != k)
				error(all, 0);
		}
	}
}

void	check_wall_around_map(t_all *all, char **map)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	while (map[i])
	{
		str = ft_strtrim(map[i], " ");
		j = 0;
		if (ft_strlen(str) && (str[0] != '1' || str[ft_strlen(str) - 1] != '1'))
		{
			free(str);
			error(all, 0);
		}
		free(str);
		if (ft_strlen(str))
			check_with_prev_string(all, map, i);
		i++;
	}
}

void	check_up_n_down(t_all *all, char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		if (i == 0 || !map[i + 1])
		{
			while (map[i][j])
			{
				if (map[i][j] != ' ' && map[i][j] != '1')
					error(all, 0);
				j++;
			}
		}
		i++;
	}
}

void	check_player(t_all *all, char **map)
{
	int	i;
	int	j;
	int	flag;

	i = 0;
	flag = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'W' ||
				map[i][j] == 'E')
				flag++;
			j++;
		}
		i++;
	}
	if (flag != 1)
		error(all, 0);
}

void	check_map(t_all *all, char **map)
{
	check_up_n_down(all, map);
	check_wall_around_map(all, map);
	check_walls_around_space(all, map);
	check_all_zeros(all, map);
	check_player(all, map);
}
