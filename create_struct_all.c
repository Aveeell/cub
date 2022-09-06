/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_struct_all.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoch <mkoch@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 13:04:54 by mkoch             #+#    #+#             */
/*   Updated: 2022/07/08 16:03:57 by mkoch            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static int	skip(char *str)
{
	int	i;

	i = 2;
	while (str[i] == ' ')
		i++;
	return (i);
}

static int	get_color(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	fill_data_stuct(t_all *all, t_tex *tex, t_data *data)
{
	int	w;
	int	h;

	all->data->mlx = mlx_init();
	data->no->img = mlx_xpm_file_to_image(data->mlx, &tex->no[skip(tex->no)], \
											&w, &h);
	data->so->img = mlx_xpm_file_to_image(data->mlx, &tex->so[skip(tex->so)], \
											&w, &h);
	data->we->img = mlx_xpm_file_to_image(data->mlx, &tex->we[skip(tex->we)], \
											&w, &h);
	data->ea->img = mlx_xpm_file_to_image(data->mlx, &tex->ea[skip(tex->ea)], \
											&w, &h);
	data->fl = get_color(0, tex->fl_rgb[0], tex->fl_rgb[1], tex->fl_rgb[2]);
	data->ceil = get_color(0, tex->cl_rgb[0], tex->cl_rgb[1], tex->cl_rgb[2]);
	if (!data->no->img || !data->so->img || !data->we->img || !data->ea->img)
		error(all, 0);
	data->no->addr = mlx_get_data_addr(data->no->img,
			&data->no->bpp, &data->no->l_len, &data->no->end);
	data->ea->addr = mlx_get_data_addr(data->ea->img,
			&data->ea->bpp, &data->ea->l_len, &data->ea->end);
	data->so->addr = mlx_get_data_addr(data->so->img,
			&data->so->bpp, &data->so->l_len, &data->so->end);
	data->we->addr = mlx_get_data_addr(data->we->img,
			&data->we->bpp, &data->we->l_len, &data->we->end);
}

t_all	*init_all(void)
{
	t_all	*all;

	all = malloc(sizeof(t_all));
	all->raw = malloc(sizeof(t_raw));
	all->tex = malloc(sizeof(t_tex));
	all->data = malloc(sizeof(t_data));
	all->data->no = malloc(sizeof(t_img));
	all->data->so = malloc(sizeof(t_img));
	all->data->we = malloc(sizeof(t_img));
	all->data->ea = malloc(sizeof(t_img));
	all->data->draw = malloc(sizeof(t_img));
	all->data->win_w = 848;
	all->data->win_h = 480;
	all->data->scale = 64;
	all->data->turn = 0.1;
	all->data->step = 10;
	all->tex->no = 0;
	all->tex->so = 0;
	all->tex->we = 0;
	all->tex->ea = 0;
	all->tex->fl = 0;
	all->tex->ceil = 0;
	all->tex->fl_rgb = malloc(sizeof(int) * 3);
	all->tex->cl_rgb = malloc(sizeof(int) * 3);
	return (all);
}
