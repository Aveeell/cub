#include "cub.h"

static void	free_array(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		free(map[i++]);
	free(map);
}

void	free_all(t_all *all)
{
	free_array(all->raw->map_raw);
	free_array(all->raw->tex_raw);
	free(all->raw);
	free(all->tex->no);
	free(all->tex->so);
	free(all->tex->we);
	free(all->tex->ea);
	free(all->tex->fl);
	free(all->tex->ceil);
	free(all->tex->fl_rgb);
	free(all->tex->cl_rgb);
	free(all->tex);
	free_array(all->lvl->map);
	mlx_destroy_image(all->lvl->mlx, all->lvl->no);
	mlx_destroy_image(all->lvl->mlx, all->lvl->so);
	mlx_destroy_image(all->lvl->mlx, all->lvl->we);
	mlx_destroy_image(all->lvl->mlx, all->lvl->ea);
	free(all->lvl->mlx);
	free(all->lvl);
	free(all);
}

void	error(t_all *all, char *where)
{
	printf("error: %s\n", where);
	free_all(all);
	exit(1);
}
