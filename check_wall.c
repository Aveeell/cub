/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_wall.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jerrok <jerrok@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 10:45:35 by jerrok            #+#    #+#             */
/*   Updated: 2022/06/21 12:43:50 by jerrok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static int check_spaces_above(char **map, int i, int j)
{
	if(map[i][j] == ' ')
		if(map[i - 1][j] != ' ' && map[i - 1][j] != '1')
		{
			printf("4\n");
			error(map, i, j);
		}
	if(map[i][j] == '0' || map[i][j] == 'N' || map[i][j] == 'S' || 
		map[i][j] == 'W' || map[i][j] == 'E')
		if(map[i - 1][j] == ' ')
			{
			printf("4\n");
			error(map, i, j);
		}
	return 0;
}

static int check_long_wall(char **map, int i)
{
	int j;
	
	j = ft_strlen(map[i - 1]);
	if(i > 0 && ft_strlen(map[i]) > ft_strlen(map[i - 1]))
	{
		if(map[i][ft_strlen(map[i - 1]) - 1] == '1')
		{
			while(map[i][j])
			{
				if(map[i][j] != '1' && map[i][j] != ' ')
				{
					printf("2\n");
					error(map, i, j);
				}
				j++;
			}
		}
	}
	return 0;
}

static int check_wall_and_space(char **map, int i)
{
	int j;

	j = 0;
	check_long_wall(map, i);
	while(map[i][j])
	{
		// if(map[i][j] != '1' && map[i][ft_strlen(map[i]) - 1] != '1')
		// {
			// printf("[%d][%d] - %s\n", i, j, map[i]);
			// error(map, i, j);
		// }
		if(i != 6)
			check_spaces_above(map, i, j);
		if(j == 0)
		{
			while(map[i][j] == ' ')
				j++;
			if(ft_strlen(map[i]) > j && (map[i][j - 1] == ' ' && map[i][j] != '1'))
			{
				printf("1\n");
				error(map, i, j);
			}
		}

		j++;
	}
	return 0;
}

int check_wall(char **map)
{
	int i;
	int j;
	
	i = 6;
	while(map[i])
	{
		j = 0;
		if(i == 6 || !map[i + 1])
		{
			check_wall_and_space(map, i);
			while(map[i][j])
			{
				if(map[i][j] != '1' && map[i][j] != ' ')
				{
					printf("3\n");
					error(map, i, j);
				}
				j++;
			}
		}
		else
			check_wall_and_space(map, i);
		i++;
	}
	return 0;
}