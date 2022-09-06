/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoch <mkoch@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 13:05:01 by mkoch             #+#    #+#             */
/*   Updated: 2022/07/08 16:00:45 by mkoch            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static void	free_array(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		free(map[i++]);
	free(map);
}

static void	free_raw(t_all *all)
{
	if (all->raw)
	{
		if (all->raw->map_raw)
			free_array(all->raw->map_raw);
		if (all->raw->tex_raw)
			free_array(all->raw->tex_raw);
		free(all->raw);
	}
}

static void	free_tex(t_all *all)
{
	if (all->tex)
	{
		if (all->tex->no)
			free(all->tex->no);
		if (all->tex->so)
			free(all->tex->so);
		if (all->tex->we)
			free(all->tex->we);
		if (all->tex->ea)
			free(all->tex->ea);
		if (all->tex->fl)
			free(all->tex->fl);
		if (all->tex->ceil)
			free(all->tex->ceil);
		if (all->tex->fl_rgb)
			free(all->tex->fl_rgb);
		if (all->tex->cl_rgb)
			free(all->tex->cl_rgb);
		free(all->tex);
	}
}

void	free_all(t_all *all)
{
	free_raw(all);
	free_tex(all);
	if (all->data)
	{
		if (all->data->map)
			free_array(all->data->map);
		if (all->data->no)
			free(all->data->no);
		if (all->data->so)
			free(all->data->so);
		if (all->data->we)
			free(all->data->we);
		if (all->data->ea)
			free(all->data->ea);
		if (all->data->draw)
			free(all->data->draw);
	}
	free(all->data);
	free(all);
	exit(0);
}

void	error(t_all *all, char *where)
{
	printf("error");
	if (where)
		printf(": %s\n", where);
	if (all)
		free_all(all);
	exit(0);
}
