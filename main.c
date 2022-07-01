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
void run_game(struct s_data data, t_all *all)
{
	data.map = all->lvl->map;
	data.mlx = all->lvl->mlx;
	all->lvl->no1 = malloc(sizeof(t_img));
	t_img *no1 = all->lvl->no1;
	no1->img = all->lvl->no;
	//----------перекрас стены
	// no1->try = mlx_new_image(data.mlx, 1, 1);
	// no1->addr = mlx_get_data_addr(no1->img, &no1->bits_per_pix, &no1->size, &no1->end);
	// // no1->try_addr = mlx_get_data_addr(no1->try, &no1->bits_per_pix, &no1->size, &no1->end);
	// printf("addr - %s\n", no1->addr);
	// printf("bpp - %d\n", no1->bits_per_pix);
	// printf("size - %d\n", no1->size);
	// printf("end - %d\n", no1->end);
	// int i = 0;
	// int j = 0;
	// no1->color = get_color(0, 4587520, 21760, 82);
	
	// printf("try_color[t] - %d\n", get_color(no1->addr[(i * (64*4) + j)], 0, 0, 0));
	// printf("try_color[r] - %d\n", get_color(0, no1->addr[(i * (64*4) + 1)],0,0));
	// printf("try_color[g] - %d\n", get_color(0,0,no1->addr[(i * (64*4) + 2)],0));
	// printf("try_color[b] - %d\n", get_color(0,0,0,no1->addr[(i * (64*4) + 3)]));


	// // printf("try_color - %x\n", )

	// printf("color - %x\n", no1->color);
	// // no1->try_addr[4 + 4] = no1->color;

	// while(i < 64)
	// {
	// 	j = 0;
	// 	while(j < 64)
	// 	{
	// 		no1->addr[(i * (64*4) + j * 4)] = no1->color;
	// 		j++;
	// 	}
	// 	i++;
	// }
	//------------------------------------------------
	ft_find_player(&data);
	data.win = mlx_new_window(data.mlx, data.win_hor_size, data.win_vert_size, "cub3d");
	ft_draw_ray(&data);
	mlx_hook(data.win, 17, 0, &exit_hook, &data);
	mlx_hook(data.win, 2, 0, key_hook, &data);
	mlx_loop(data.mlx);
}
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