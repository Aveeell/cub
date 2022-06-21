#include "cub.h"

//1, 0, N, S, E, W, F, C, NO, SO, WE, EA

void error(char **map, int i, int j)
{
	if(map)
		printf("[%d][%d] - |%s|\n", i, j, map[i]);
	printf("error\n");
	exit(0);
}

char **get_map(char *map_file)
{
	char **map;
	char *read;
	char *line;
	int fd;
	int i;

	fd = open(map_file, O_RDONLY);
	if (fd == -1)
		error(0,0,0);
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
	i = ft_strlen(read) - 1;
	while(read[i] == '\n')
		read[i--] = '\0';
	map = ft_split(read, '\n');
	return (map);
}

int check_symbols(char **map)
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
				{
					printf("|%c|\n", map[i][j]);
					error(map,i,j);
				}
			j++;
		}
		i++;
	}
	return 0;
}
//NO SO WE EA F C

int check_map(char **map)
{
	check_symbols(map);
	check_wall(map);
	return 0;
}

int get_start_of_map(char **map_raw)
{
	int i;
	int j;

	i = 0;
	while(map_raw[i])
	{
		j = 0;
		while(map_raw[i][j])
		{
			if(map_raw[i][j] != ' ' && map_raw[i][j] != '1')
				break;
			j++;
		}
		if(j == ft_strlen(map_raw[i]))
			break;
		i++;
	}
	return i;
}

char **get_textures(char **map)
{
	int i;
	char **textures;

	i = get_start_of_map(map);
	textures = malloc(sizeof(char **) * i + 1);
	textures[i] = 0;
	while(i)
	{
		i--;
		textures[i] = ft_strdup(map[i], 0);
	}
	return textures;
}

char **get_only_map(char **map_raw)
{
	int i;
	int j;
	char **map;

	i = get_start_of_map(map_raw);
	j = i;
	while(map_raw[j])
		j++;
	map = malloc(sizeof(char **) * j - i + 1);
	j = 0;
	while(map_raw[i])
	{
		map[j] = ft_strdup(map_raw[i], 0);
		j++;
		i++;
	}
	map[j] = 0;
	return map;
}

int main(int argc, char **argv)
{
	char **map_raw;
	char **map;
	char **textures;

	if(argc != 2 || ft_strncmp(&argv[1][ft_strlen(argv[1]) - 4], ".cub", 4))
		printf("Try ./cub3D <map_file.cub>\n");
	else
	{
		map_raw = get_map(argv[1]);
		if(!map_raw)
			error(0,0,0);
		map = get_only_map(map_raw);
		textures = get_textures(map_raw);
		for(int i = 0; map[i]; i++)
			free(map[i]);
		free(map);

	// for(int i = 0; map[i]; i++)
	// 	printf("|%s|\n", map[i]);

		check_map(map);
	}
	return 0;
}