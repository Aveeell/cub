#include "cub.h"

int get_middle_of_map_file(char **map_raw)
{
	int i;
	int j;

	i = 0;
	while(map_raw[i])
	{
		j = 0;
		while(map_raw[i][j])
		{
			if(map_raw[i][j] != '1' && map_raw[i][j] != ' ' && map_raw[i][j] != '0')
				break;
			j++;
		}
		if(j == ft_strlen(map_raw[i]))
			break;
		i++;
	}
	return i;
}

int get_start_of_map(char **map_raw)
{
	int i;
	int j;

	i = get_middle_of_map_file(map_raw);
	while(map_raw[i])
	{
		j = 0;
		while(map_raw[i][j])
		{
			if(map_raw[i][j] != ' ')
				break;
			j++;
		}
		if(j != ft_strlen(map_raw[i]))
				break;
		i++;
	}
	return i;
}

int get_end_of_map(char **map_raw, int i)
{
	int k;
	int j;

	j = i;
	while(map_raw[j])
		j++;
	while(map_raw[j])
	{
		k = 0;
		while(map_raw[j][k])
		{
			if(map_raw[j][k] != ' ')
				break;
			k++;
		}
		if(k != ft_strlen(map_raw[j]))
			break;
		j--;
	}
	return j;
}

void check_symbols_on_map(char **map)
{
	int i;
	int j;
	char *str;
	
	i = 0;
	while(map[i])
	{
		j = 0;
		str = map[i];
		while(map[i][j])
		{
			if(str[j] != ' ' && str[j] != '0' && str[j] != '1' &&
				str[j] != 'N' && str[j] != 'S' && str[j] != 'W' &&
				str[j] != 'E')
					error(map,i,j, "check_symbols");
			j++;
		}
		i++;
	}
}

char **get_only_map(char **map_raw)
{
	int i;
	int j;
	char **map;

	i = get_start_of_map(map_raw);
	j = get_end_of_map(map_raw, i);
	map = malloc(sizeof(char **) * j - i + 1);
	if(!map)
		return 0;
	j = 0;
	while(map_raw[i])
	{
		map[j] = ft_strdup(map_raw[i], 0);
		if(map[j][0] == '\n')
			error(map, j, 0, "newline in map");
		j++;
		i++;
	}
	map[j] = 0;
	check_symbols_on_map(map);
	return map;
} //19

char **get_textures(char **map_raw)
{
	int i;
	char **textures;

	i = get_middle_of_map_file(map_raw);
	if(i != 6)
		error(map_raw,i,0, "get_textures");
	textures = malloc(sizeof(char **) * i + 1);
	if(!textures)
		return 0;
	textures[i] = 0;
	while(i)
	{
		i--;
		textures[i] = ft_strdup(map_raw[i], 0);
	}
	return textures;
}

char **get_map(char *map_file)
{
	char **map;
	char *read;
	char *line;
	int fd;

	fd = open(map_file, O_RDONLY);
	if (fd == -1)
		error(0,0,0, "get_map");
	read = NULL;
	line = get_next_line(fd);
	while (line)
	{
		read = ft_strjoin(read, line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	free(line);
	line = ft_strtrim(read, " \n");
	free(read);
	map = ft_split(line, '\n');
	return (map);
}