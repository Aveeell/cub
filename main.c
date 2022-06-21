#include "cub.h"

//1, 0, N, S, E, W, F, C, NO, SO, WE, EA

void error(char **map, int i, int j)
{
	if(map && i && j)
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
	map = ft_split(read, '\n');
	return (map);
}

int check_symbols(char **map)
{
	int i;
	int j;
	char *str;
	
	i = 6;
	while(map[i])
	{
		j = 0;
		str = map[i];
		while(map[i][j])
		{
			if(str[j] != ' ' && str[j] != '0' && str[j] != '1' &&
				str[j] != 'N' && str[j] != 'S' && str[j] != 'W' &&
				str[j] != 'E')
				error(0,0,0);
			j++;
		}
		i++;
	}
	return 0;
}
//NO SO WE EA F C
// int check_textures(char **map)
// {
// 	int i;
// 	int j;
// 	int check[5];
	
// 	i = 0;
// 	while(i < 6)
// 	{
// 		j = 0;
// 		while(map[i][j] == ' ')
// 			j++;
// 		if()
// 	}
// }

int check_map(char **map)
{
	check_symbols(map);
	check_wall(map);
	return 0;
}

int main(int argc, char **argv)
{
	char **map;
	
	if(argc != 2 || ft_strncmp(&argv[1][ft_strlen(argv[1]) - 4], ".cub", 4))
		printf("Try ./cub3D <map_file.cub>\n");
	else
	{
		map = get_map(argv[1]);
		if(!map)
			error(0,0,0);
		// else
		// 	for(int i = 0; map[i]; i++)
		// 		printf("%s\n", map[i]);
		check_map(map);
	}
	return 0;
}