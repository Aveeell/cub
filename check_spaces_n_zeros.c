/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_spaces_n_zeros.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoch <mkoch@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 13:04:41 by mkoch             #+#    #+#             */
/*   Updated: 2022/07/08 16:01:21 by mkoch            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static int	is_full_space(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ')
		i++;
	if (i == ft_strlen(str))
		return (1);
	return (0);
}

void	check_walls_around_space(t_all *all, char **map)
{
	int	i;
	int	j;

	i = 1;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == ' ')
			{
				if ((j < ft_strlen(map[i - 1]) && (map[i - 1][j] != ' ' && \
					map[i - 1][j] != '1')) || \
					(!is_full_space(map[i]) && j > 0 && \
					(map[i][j - 1] != ' ' && map[i][j - 1] != '1')) || \
					(j < ft_strlen(map[i + 1]) && (map[i + 1][j] != ' ' && \
					map[i + 1][j] != '1')) || \
					(!is_full_space(map[i]) && j < ft_strlen(map[i]) && \
					(map[i][j + 1] != ' ' && map[i][j + 1] != '1')))
					error(all, 0);
			}
			j++;
		}
		i++;
	}
}

void	check_all_zeros(t_all *all, char **map)
{
	int	i;
	int	j;

	i = 1;
	while (map[i])
	{
		j = 1;
		while (map[i][j])
		{
			if (map[i][j] == '0' || map[i][j] == 'N' || map[i][j] == 'S' ||
				map[i][j] == 'W' || map[i][j] == 'E')
				if ((map[i - 1][j] == ' ' || !map[i - 1][j]) ||
					(map[i + 1][j] == ' ' || !map[i + 1][j]) ||
					(map[i][j - 1] == ' ' || !map[i][j - 1]) ||
					(map[i][j + 1] == ' ' || !map[i][j + 1]) ||
					(map[i + 1][j - 1] == ' ' || !map[i + 1][j - 1]) ||
					(map[i + 1][j + 1] == ' ' || !map[i + 1][j + 1]) ||
					(map[i - 1][j + 1] == ' ' || !map[i - 1][j + 1]) ||
					(map[i - 1][j - 1] == ' ' || !map[i - 1][j - 1]))
					error(all, 0);
			j++;
		}
		i++;
	}
}
