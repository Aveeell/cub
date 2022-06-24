#include "cub.h"

void free_array(char **map)
{
	int i;
	
	i = 0;
	while(map[i])
		free(map[i++]);
	free(map);
}

void free_all(t_all *all)
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
		free(all->tex->ceil_rgb);
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

void error(t_all *all, char *where)
{
	printf("error: %s\n", where);
	free_all(all);
	exit(1);
}

t_all *init_all()
{
	t_all *all;

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
	all->tex->ceil_rgb = malloc(sizeof(int) * 3);
	return (all);
}

int skip(char *str)
{
	int i;

	i = 2;
	while (str[i] == ' ')
		i++;
	return (i);
}

int	get_color(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void fill_lvl_stuct(t_all *all, t_tex *tex, t_lvl *lvl)
{
	int w;
	int h;

	lvl->mlx = mlx_init();
	lvl->win = mlx_new_window(lvl->mlx, 300, 300, "test");
	lvl->no = mlx_xpm_file_to_image(lvl->mlx, &tex->no[skip(tex->no)], &w, &h);
	lvl->so = mlx_xpm_file_to_image(lvl->mlx, &tex->so[skip(tex->so)], &w, &h);
	lvl->we = mlx_xpm_file_to_image(lvl->mlx, &tex->we[skip(tex->we)], &w, &h);
	lvl->ea = mlx_xpm_file_to_image(lvl->mlx, &tex->ea[skip(tex->ea)], &w, &h);
	lvl->fl = get_color(0, tex->fl_rgb[0], tex->fl_rgb[1], tex->fl_rgb[2]);
	lvl->ceil = get_color(0, tex->ceil_rgb[0], tex->ceil_rgb[1], tex->ceil_rgb[2]);
	mlx_destroy_window(lvl->mlx, lvl->win);
	if(!lvl->no || !lvl->so || !lvl->we || !lvl->ea)
		error(all,"can't open file with textures");
}

int main(int argc, char **argv)
{
	t_all *all;

	if (argc != 2 || ft_strncmp(&argv[1][ft_strlen(argv[1]) - 4], ".cub", 4))
		printf("Try ./cub3D <map_file.cub>\n");
	else
	{
		all = init_all();
		all->raw->map_raw = get_map(argv[1]);
		if(!all->raw->map_raw)
			error(all, "error in split");
		all->lvl->map = get_only_map(all, all->raw->map_raw);
		check_map(all, all->lvl->map);
		all->raw->tex_raw = get_textures(all, all->raw->map_raw);
		get_struct(all, all->raw->tex_raw, all->tex);
		fill_lvl_stuct(all, all->tex, all->lvl);
		free_all(all);
	}
	return (0);
}