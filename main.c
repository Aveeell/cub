/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jerrok <jerrok@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 11:08:19 by jerrok            #+#    #+#             */
/*   Updated: 2022/06/22 14:48:56 by jerrok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

//1, 0, N, S, E, W, F, C, NO, SO, WE, EA

void error(char **map, int i, int j, char *where)
{
	if(map)
		printf("[%d][%d] - |%s|\n", i, j, map[i]);
	printf("error: %s\n", where);
	exit(0);
}

// char *gnl(int fd)
// {
// 	int rd;
// 	int i;
// 	char c;
// 	char *str;
//
// 	i = 0;
// 	str = malloc(10000);
// 	while((rd = read(fd, &c, 1)) > 0)
// 	{
// 		str[i] = c;
// 		i++;
// 		if(c == '\n')
// 			break;
// 	}
// 	if((!str[i-1] && !rd) || rd == -1)
// 	{
// 		free(str);
// 		return 0;
// 	}
// 	str[i] = 0;
// 	return str;
// }

char **get_map(char *map_file)
{
	char **map;
	char *read;
	char *line;
	int i;
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
	i = ft_strlen(read);
	// printf("i = %d\n", i);
	// while(read[i])
	// {
	// 	i--;
	// 	read[i] = 0;
	// }
	// printf("%s|", read);
	map = ft_split(read, '\n');
	return (map);
}

void	print(char **map)
{
	for(int i = 0; map[i]; i++)
		printf("%d\t| %s\n", i, map[i]);
}


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
				{
					printf("|%c|\n", map[i][j]);
					error(map,i,j, "check_symbols");
				}
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
		error(0,0,0, "get_textures");
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


int check_map(char **map)
{
	check_wall(map);
	return 0;
}


void free_array(char **map)
{
	int i;
	
	i = 0;
	while(map[i])
		free(map[i++]);
	free(map);
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
			error(0,0,0, "main");
			
		// printf("-----------------raw-----------------\n");
		// print(map_raw);
		
		map = get_only_map(map_raw);
		printf("-----------------map-----------------\n");
		print(map);
		printf("-------------------------------------\n");
		
		textures = get_textures(map_raw);
		// printf("-----------------tex-----------------\n");
		// print(textures);
		
		free_array(map_raw);
		check_map(map);
		free_array(map);
		free_array(textures);
	}
	return 0;
}