#include "cub.h"

int	check_symbols_on_map(char **map)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	while (map[i])
	{
		j = 0;
		str = map[i];
		while (map[i][j])
		{
			if (str[j] != ' ' && str[j] != '0' && str[j] != '1' && \
				str[j] != 'N' && str[j] != 'S' && str[j] != 'W' && \
				str[j] != 'E')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

char	**get_only_map(t_all *all, char **map_raw)
{
	int		i;
	int		j;
	char	**map;

	i = get_start_of_map(map_raw);
	j = get_end_of_map(map_raw, i);
	map = malloc(sizeof(char **) * j - i + 1);
	if (!map)
		error(all, "get_only_map mem alloc failed");
	j = 0;
	while (map_raw[i])
	{
		map[j] = ft_strdup(map_raw[i], 0);
		if (!map[j])
			error(all, "get_only_map mem alloc failed (strdup)");
		j++;
		i++;
	}
	map[j] = 0;
	if (!check_symbols_on_map(map))
		error(all, "check_symbols wrong symbols on map");
	return (map);
}

char	**get_textures(t_all *all, char **map_raw)
{
	int		i;
	char	**textures;

	i = get_middle_of_map_file(map_raw);
	if (i != 6)
		error(all, "get_textures tex != 6");
	textures = malloc(sizeof(char **) * i + 1);
	if (!textures)
		error(all, "get_textures mem alloc failed");
	textures[i] = 0;
	while (i)
	{
		i--;
		textures[i] = ft_strdup(map_raw[i], 0);
		if (!textures[i])
			error(all, "get_textures mem alloc failed (strdup)");
	}
	return (textures);
}

char	**get_map(char *map_file)
{
	char	**map;
	char	*read;
	char	*line;
	int		fd;

	fd = open(map_file, O_RDONLY);
	if (fd == -1)
		error(0, "can't open map file");
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
