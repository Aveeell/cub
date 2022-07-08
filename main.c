/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoch <mkoch@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 13:05:15 by mkoch             #+#    #+#             */
/*   Updated: 2022/07/08 13:06:13 by mkoch            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static void	get_all_struct(char *argv, t_all *all)
{
	all->raw->map_raw = get_map(argv);
	if (!all->raw->map_raw)
		error(0, "can't open file");
	all->data->map = get_only_map(all, all->raw->map_raw);
	check_map(all, all->data->map);
	all->raw->tex_raw = get_textures(all, all->raw->map_raw);
	get_struct_textures(all, all->raw->tex_raw, all->tex);
	fill_data_stuct(all, all->tex, all->data);
}

void	run_game(t_data *data, t_all *all)
{
	int	k;

	k = 0;
	ft_find_player(data);
	data->draw->img = mlx_new_image(data->mlx, data->win_w, data->win_h);
	data->draw->addr = mlx_get_data_addr(data->draw->img, &data->draw->bpp, \
										&data->draw->l_len, &data->draw->end);
	data->win = mlx_new_window(data->mlx, data->win_w, data->win_h, "cub3d");
	while (data->map[k])
		k++;
	data->scale_minimap = (int)(0.3 * data->win_h / k);
	mlx_hook(data->win, 17, 0, exit_hook, all);
	mlx_hook(data->win, 2, 0, key_hook, all);
	mlx_mouse_hook(data->win, mouse_toogle, data);
	mlx_hook(data->win, 6, 0, mouse_move, data);
	mlx_loop_hook(data->mlx, render, data);
	mlx_loop(data->mlx);
}

int	main(int argc, char **argv)
{
	t_all	*all;

	if (argc != 2 || ft_strncmp(&argv[1][ft_strlen(argv[1]) - 4], ".cub", 4))
		printf("Try ./cub3D <map_file.cub>\n");
	else
	{
		all = init_all();
		get_all_struct(argv[1], all);
		run_game(all->data, all);
	}
	return (0);
}
