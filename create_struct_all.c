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

void	fill_lvl_stuct(t_all *all, t_tex *tex, t_lvl *lvl)
{
	int	w;
	int	h;

	all->lvl->mlx = mlx_init();
	lvl->no = mlx_xpm_file_to_image(lvl->mlx, &tex->no[skip(tex->no)], &w, &h);
	lvl->so = mlx_xpm_file_to_image(lvl->mlx, &tex->so[skip(tex->so)], &w, &h);
	lvl->we = mlx_xpm_file_to_image(lvl->mlx, &tex->we[skip(tex->we)], &w, &h);
	lvl->ea = mlx_xpm_file_to_image(lvl->mlx, &tex->ea[skip(tex->ea)], &w, &h);
	lvl->fl = get_color(0, tex->fl_rgb[0], tex->fl_rgb[1], tex->fl_rgb[2]);
	lvl->ceil = get_color(0, tex->cl_rgb[0], tex->cl_rgb[1], tex->cl_rgb[2]);
	if (!lvl->no || !lvl->so || !lvl->we || !lvl->ea)
		error(all, "can't open file with textures");
}

t_all	*init_all(void)
{
	t_all	*all;

	all = malloc(sizeof(t_all));
	all->lvl = malloc(sizeof(t_lvl));
	all->raw = malloc(sizeof(t_raw));
	all->tex = malloc(sizeof(t_tex));
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
