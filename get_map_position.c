#include "cub.h"

int	get_middle_of_map_file(char **map_raw)
{
	int	i;
	int	j;

	i = 0;
	while (map_raw[i])
	{
		j = 0;
		while (map_raw[i][j])
		{
			if (map_raw[i][j] != '1' && map_raw[i][j] != ' ' && \
				map_raw[i][j] != '0')
				break ;
			j++;
		}
		if (j == ft_strlen(map_raw[i]))
			break ;
		i++;
	}
	return (i);
}

int	get_start_of_map(char **map_raw)
{
	int	i;
	int	j;

	i = get_middle_of_map_file(map_raw);
	while (map_raw[i])
	{
		j = 0;
		while (map_raw[i][j])
		{
			if (map_raw[i][j] != ' ')
				break ;
			j++;
		}
		if (j != ft_strlen(map_raw[i]))
			break ;
		i++;
	}
	return (i);
}

int	get_end_of_map(char **map_raw, int i)
{
	int	k;
	int	j;

	j = i;
	while (map_raw[j])
		j++;
	while (map_raw[j])
	{
		k = 0;
		while (map_raw[j][k])
		{
			if (map_raw[j][k] != ' ')
				break ;
			k++;
		}
		if (k != ft_strlen(map_raw[j]))
			break ;
		j--;
	}
	return (j);
}
