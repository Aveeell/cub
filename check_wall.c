#include "cub.h"

static int check_spaces_above(char **map, int i, int j)
{
	if(i > 6)
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
	}
	return 0;
}

static int check_long_wall(char **map, int i)
{
	int j;
	
	j = ft_strlen(map[i - 1]);
	if(i > 6 && ft_strlen(map[i]) > ft_strlen(map[i - 1]))
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
	check_spaces_above(map, i, j);
	while(map[i][j])
	{
		while(map[i][j] == ' ')
			j++;
		if(ft_strlen(map[i]) > j && (map[i][j - 1] == ' ' && map[i][j] != '1'))
		{
			printf("1\n");
			error(map, i, j);
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