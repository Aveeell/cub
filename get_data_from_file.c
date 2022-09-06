/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data_from_file.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoch <mkoch@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 13:05:05 by mkoch             #+#    #+#             */
/*   Updated: 2022/07/08 16:01:06 by mkoch            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	check_symbols_on_map(char **map)
{
	int		i;
	int		j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] != ' ' && map[i][j] != '0' && map[i][j] != '1' && \
				map[i][j] != 'N' && map[i][j] != 'S' && map[i][j] != 'W' && \
				map[i][j] != 'E')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

void	get_only_map(t_all *all, char **map_raw)
{
	int		i;
	int		j;

	i = get_start_of_map(map_raw);
	j = get_end_of_map(map_raw, i);
	if (!check_symbols_on_map(&map_raw[i]))
	{
		all->data->map = 0;
		error(all, 0);
	}
	all->data->map = malloc(sizeof(char *) * j - i);
	if (!all->data->map)
		error(all, 0);
	j = 0;
	while (map_raw[i])
	{
		all->data->map[j] = ft_strdup(map_raw[i], 0);
		if (!all->data->map[j])
			error(all, 0);
		j++;
		i++;
	}
	all->data->map[j] = 0;
}

char	**get_textures(t_all *all, char **map_raw)
{
	int		i;
	char	**textures;

	i = get_middle_of_map_file(map_raw);
	if (i != 6)
		error(all, 0);
	textures = malloc(sizeof(char **) * i + 1);
	if (!textures)
		error(all, 0);
	textures[i] = 0;
	while (i)
	{
		i--;
		textures[i] = ft_strdup(map_raw[i], 0);
		if (!textures[i])
			error(all, 0);
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
		error(0, 0);
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
