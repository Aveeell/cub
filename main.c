/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jerrok <jerrok@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 11:08:19 by jerrok            #+#    #+#             */
/*   Updated: 2022/06/23 17:19:00 by jerrok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

//F, C, NO, SO, WE, EA

void error(char **map, int i, int j, char *where)
{
	if(map)
		printf("[%d][%d] - |%s|\n", i, j, map[i]);
	printf("error: %s\n", where);
	exit(0);
}

void	print(char **arr, t_textures *textures)
{
	if(arr)
		for(int i = 0; arr[i]; i++)
			printf("%d\t| %s\n", i, arr[i]);
	if(textures)
	{
		printf("no - %s\n", textures->no);
		printf("so - %s\n", textures->so);
		printf("we - %s\n", textures->we);
		printf("ea - %s\n", textures->ea);
		printf("fl_str - %s\n", textures->fl);
		printf("ceil_str - %s\n", textures->ceil);
		printf("fl_rgb - ");
		for(int i = 0; i < 3; i++)
			printf("%d | ", textures->fl_rgb[i]);
		printf("\nceil_rgb - ");
		for(int i = 0; i < 3; i++)
			printf("%d | ", textures->ceil_rgb[i]);
	}
}

void free_array(char **map)
{
	int i;
	
	i = 0;
	while(map[i])
		free(map[i++]);
	free(map);
}

t_textures	*init_tex(void)
{
	t_textures	*tex;

	tex = malloc(sizeof(t_textures));
	tex->no = 0;
	tex->so = 0;
	tex->we = 0;
	tex->ea = 0;
	tex->fl = 0;
	tex->ceil = 0;
	tex->fl_rgb = malloc(sizeof(int) * 3);
	tex->ceil_rgb = malloc(sizeof(int) * 3);
	return (tex);
}

int main(int argc, char **argv)
{
	char **map_raw;
	char **map;
	char **textures_raw;
	t_textures *textures;

	if(argc != 2 || ft_strncmp(&argv[1][ft_strlen(argv[1]) - 4], ".cub", 4))
		printf("Try ./cub3D <map_file.cub>\n");
	else
	{
		map_raw = get_map(argv[1]);
		if(!map_raw)
			error(0,0,0, "main");
			
		printf("-----------------raw-----------------\n");
		print(map_raw, 0);
		
		map = get_only_map(map_raw);
		printf("-----------------map-----------------\n");
		print(map, 0);
		
		textures_raw = get_textures(map_raw);
		printf("-----------------tex-----------------\n");
		print(textures_raw, 0); 
		
		printf("\n----------------check-------------------\n");
		textures = init_tex();
		get_struct(textures_raw, textures);
		print(0, textures);

		check_map(map);
		
		free_array(map_raw);
		free_array(map);
		free_array(textures_raw);
	}
	return 0;
}