#include "cub.h"

/*
static int check_spaces_above(char **map, int i, int j)
{
	if(i > 0)
	{
		while(map[i][j])
		{
		if(map[i][j] == ' ' && (ft_strlen(map[i]) == ft_strlen(map[i - 1])))
			if(map[i - 1][j] != ' ' && map[i - 1][j] != '1')
			{
				printf("4.1\n");
				error(map, i, j);
			}
		if(map[i][j] == '0' || map[i][j] == 'N' || map[i][j] == 'S' || 
			map[i][j] == 'W' || map[i][j] == 'E')
			if(map[i - 1][j] == ' ')
				{
				printf("4.2\n");
				error(map, i, j);
			}
			j++;
		}
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

static int check_corner(char **map, int i, int j)
{
	j++;
	if(i == 0)
	{
		if(map[i][j] == '0')
			if(map[i - 1][j - 1] != '1')
				error(map, i, j);
		j = ft_strlen(map[i]) - 2;
		if(map[i][j] == '0')
			if(map[i - 1][j + 1] != '1')
				error(map, i, j);
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
		check_corner(map, i, j);
		if(ft_strlen(map[i]) > j && (map[i][j - 1] == ' ' && map[i][j] != '1'))
		{
			printf("1\n");
			error(map, i, j);
		}
		j++;
	}
	return 0;
}
*/

void check_with_prev_string(char **map, int i)
{
	int j;
	int k;

	if(i > 0)
	{
		j = ft_strlen(map[i]) - 1;
		k = ft_strlen(map[i - 1]) - 1;
		if(j > k)
		{
			if(map[i][k] != '1')
				error(map, i, j, "check_with_prev | no wall in pos");
			while(j > k)
			{
				if(map[i][j] != ' ' && map[i][j] != '1')
					break;
				j--;
			}
			if(j != k)
				error(map, i, j, "check_with_prev");
		}
	}
}

void check_wall_around_map(char **map)
{
	int i;
	int j;
	char *str;

	i = 0;
	while(map[i])
	{
		str = ft_strtrim(map[i], " ");
		j = 0;
		if(ft_strlen(str) && (str[0] != '1' || str[ft_strlen(str) - 1] != '1'))
		{
		printf("\n|%d|\n", ft_strlen(str));
			free(str);
			error(map, i, ft_strlen(map[i]), "check_wall_around | first\\last wall");
		}
		if(ft_strlen(str))
			check_with_prev_string(map, i);
		free(str);
		i++;
	}
}

void check_up_n_down(char **map)
{
	int i;
	int j;

	i = 0;
	while(map[i])
	{
		j = 0;
		if(i == 0 || !map[i + 1])
		{
			while(map[i][j])
			{
				if(map[i][j] != ' ' && map[i][j] != '1')
					error(map, i, j, "up_n_down");
				j++;
			}
		}
		i++;
	}
}

void check_walls_around_space(char **map)
{
	int i;
	int j;

	i = 1;
	while(map[i])
	{
		j = 0;
		while(map[i][j])
		{
			if(map[i][j] == ' ')
			{
				if(j < ft_strlen(map[i - 1]) && (map[i - 1][j] != ' ' && map[i - 1][j] != '1'))
					error(map, i, j, "check_space above");
				if(j > 0 && (map[i][j - 1] != ' ' && map[i][j - 1] != '1'))
					error(map, i, j, "check_space left");
				if(j < ft_strlen(map[i + 1]) && (map[i + 1][j] != ' ' && map[i + 1][j] != '1'))
					error(map, i, j, "check_space bottom");
				if(j < ft_strlen(map[i]) && (map[i][j + 1] != ' ' && map[i][j + 1] != '1'))
					error(map, i, j, "check_space right");
			}
			j++;
		}
		i++;
	}
}

int check_wall(char **map)
{
	check_up_n_down(map);
	check_wall_around_map(map);
	check_walls_around_space(map);
	return 0;
}