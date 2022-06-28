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
	if (all->lvl)
	{
		if (all->lvl->map)
			free_array(all->lvl->map);
		if (all->lvl->no)
			mlx_destroy_image(all->lvl->mlx, all->lvl->no);
		if (all->lvl->so)
			mlx_destroy_image(all->lvl->mlx, all->lvl->so);
		if (all->lvl->we)
			mlx_destroy_image(all->lvl->mlx, all->lvl->we);
		if (all->lvl->ea)
			mlx_destroy_image(all->lvl->mlx, all->lvl->ea);
		if (all->lvl->mlx)
			free(all->lvl->mlx);
		free(all->lvl);
	}
	free(all);
	exit(0);
}

void	error(t_all *all, char *where)
{
	printf("error: %s\n", where);
	if (all)
		free_all(all);
	exit(0);
}
