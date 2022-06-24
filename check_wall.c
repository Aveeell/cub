#include "cub.h"

void check_with_prev_string(t_all *all, char **map, int i)
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
				error(all, "check_with_prev | no wall bottom last symbol from prev string");
			while(j > k)
			{
				if(map[i][j] != ' ' && map[i][j] != '1')
					break;
				j--;
			}
			if(j != k)
				error(all, "check_with_prev");
		}
	}
}

void check_wall_around_map(t_all *all, char **map)
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
			error(all, "check_wall_around | first\\last wall");
		}
		if(ft_strlen(str))
			check_with_prev_string(all, map, i);
		free(str);
		i++;
	}
}

void check_up_n_down(t_all *all, char **map)
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
					error(all, "up_n_down");
				j++;
			}
		}
		i++;
	}
}

int is_full_space(char *str)
{
	int i;

	i = 0;
	while(str[i] == ' ')
		i++;
	if(i == ft_strlen(str))
		return 1;
	return 0;
}

void check_walls_around_space(t_all *all, char **map)
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
					error(all, "check_space above");
				if(!is_full_space(map[i]) && j > 0 && (map[i][j - 1] != ' ' && map[i][j - 1] != '1'))
					error(all, "check_space left");
				if(j < ft_strlen(map[i + 1]) && (map[i + 1][j] != ' ' && map[i + 1][j] != '1'))
					error(all, "check_space bottom");
				if(!is_full_space(map[i]) && j < ft_strlen(map[i]) && (map[i][j + 1] != ' ' && map[i][j + 1] != '1'))
					error(all, "check_space right");
			}
			j++;
		}
		i++;
	}
}

void check_all_zeros(t_all *all, char **map)
{
	int i;
	int j;

	i = 1;
	while(map[i])
	{
		j = 1;
		while(map[i][j])
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
						error(all,"check_zeros");
			j++;
		}
		i++;
	}
}

void check_player(t_all *all, char **map)
{
	int i;
	int j;
	int flag;

	i = 0;
	flag = 0;
	while(map[i])
	{
		j = 0;
		while(map[i][j])
		{
			if(map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'W' ||
				map[i][j] == 'E')
				flag++;
			j++;
		}
		i++;
	}
	if(flag != 1)
		error(all,"check_player");
}

int check_map(t_all *all, char **map)
{
	check_up_n_down(all, map);
	check_wall_around_map(all, map);
	check_walls_around_space(all, map);
	check_all_zeros(all, map);
	check_player(all, map);
	return 0;
}