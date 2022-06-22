/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jerrok <jerrok@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 11:08:19 by jerrok            #+#    #+#             */
/*   Updated: 2022/06/22 11:59:55 by jerrok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	int i;
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
	i = ft_strlen(read) - 1;
	while(read[i] == '\n' || read[i] == ' ')
		read[i--] = '\0';
	map = ft_split(read, '\n');
	return (map);
}

void	print(char **map)
{
	for(int i = 0; map[i]; i++)
		printf("%s\n", map[i]);
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
					error(map,i,j);
				}
			j++;
		}
		i++;
	}
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
			if(map_raw[i][j] != '1' && map_raw[i][j] != ' ')
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
		error(0,0,0);
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

void free_map_raw(char **map)
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
			error(0,0,0);
			
		// printf("-----------------raw-----------------\n");
		// print(map_raw);
		
		printf("-----------------map-----------------\n");
		map = get_only_map(map_raw);
		print(map);
		
		printf("-----------------tex-----------------\n");
		textures = get_textures(map_raw);
		print(textures);
		
		free_map_raw(map_raw);
		// check_map(map);
	}
	return 0;
}