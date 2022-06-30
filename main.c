#include "cub.h"

static void	get_all_struct(char *argv, t_all *all)
{
	all->raw->map_raw = get_map(argv);
	if (!all->raw->map_raw)
		error(0, "can't open file");
	all->lvl->map = get_only_map(all, all->raw->map_raw);
	check_map(all, all->lvl->map);
	all->raw->tex_raw = get_textures(all, all->raw->map_raw);
	get_struct(all, all->raw->tex_raw, all->tex);
	fill_lvl_stuct(all, all->tex, all->lvl);
}
//----------------------------------------------------------------------------------------
// void	pix_to_img(t_img *img, int x, int y, int color)
// {
// 	char	*addr;

// 	addr = img->cur_addr + (y * img->size + x * (img->bit_per_pix / 8));
// 	*(unsigned int *)addr = color;
// }
//-----------------------------------------------------------------------------------------
int	main(int argc, char **argv)
{
	t_all	*all;

	struct s_data data;
	data.height = 1000;
	data.width = 1000;
	data.num_rows = 7;
	data.scale = 64; //size of texture
	data.win_hor_size = 848; //window horizontal size
	data.win_vert_size = 480; //window vertical size

	if (argc != 2 || ft_strncmp(&argv[1][ft_strlen(argv[1]) - 4], ".cub", 4))
		printf("Try ./cub3D <map_file.cub>\n");
	else
	{
		all = init_all();
		data.all = all;
		get_all_struct(argv[1], all);
		run_game(data, all);
	}
	return (0);
}

/*
если объявить mlx в структуре lvl или all, то будет утечка на [98304]
если объявить mlx просто в main(), утечки нет
*/