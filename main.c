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
//---------------------------------------------------
void	ft_put_pixel_scale(t_data *data, float i, float j, int color)
{
	int	x;
	int	y;

	x = j * data->scale;
	while (x < data->scale * (j + 1))
	{
		y = i * data->scale;
		while (y < data->scale * (i + 1))
		{
			mlx_pixel_put(data->mlx, data->win, x, y, color);
			y++;
		}
		x++;
	}
}

void	draw_column(t_data *data, float len, int j)
{
	float	start;
	float	finish;

	start = (data->win_vert / 2) - data->scale * data->win_vert / len;
	finish = (data->win_vert / 2) + data->scale * data->win_vert / len;
	// mlx_put_image_to_window(data->mlx, data->win, data->all->lvl->no, j, start);
	while ((int) start < (int) finish)
	{
		mlx_pixel_put(data->mlx, data->win, j, start, 0xAAAAAAAA);
		start++;
	}
}

float	ft_one_ray(t_data *data, float pov_tmp)
{
	float	x;
	float	y;
	float	len;

	x = data->pl_x;
	y = data->pl_y;
	while (data->map[(int)(y / data->scale)][(int)(x / data->scale)] != '1')
	{
		x += cos(pov_tmp);
		y += sin(pov_tmp);
		// l++;
	}
	// printf("l = %d\n", l);
	len = sqrt(pow((data->pl_y - y), 2) + pow((data->pl_x - x), 2)); // долго!!
	// len = l;
	len *= cos(data->pl_pov - pov_tmp);
	return (len);
}

void	ft_draw_ray(t_data *data)
{
	float	len;
	float	pov_tmp;
	float	delta_angle;
	int		j;

	j = 0;
	pov_tmp = data->pl_pov - M_PI / 4;
	delta_angle = (M_PI / 2) / data->win_hor;
	while (j < data->win_hor)
	{
		len = ft_one_ray(data, pov_tmp); // or find len l++;
		draw_column(data, len, j);
		pov_tmp += delta_angle; // 90/320
		j++;
	}
}

//-----------------------------------------------------------------------------------------
int	main(int argc, char **argv)
{
	t_all	*all;
	t_data	data;

	data.step = 20;
	data.turn = 0.1;
	data.scale = 225; //size of texture
	data.win_hor = 848; //window horizontal size
	data.win_vert = 480; //window vertical size
	if (argc != 2 || ft_strncmp(&argv[1][ft_strlen(argv[1]) - 4], ".cub", 4))
		printf("Try ./cub3D <map_file.cub>\n");
	else
	{
		all = init_all();
		data.all = all;
		get_all_struct(argv[1], all);
		data.map = all->lvl->map;
		data.mlx = all->lvl->mlx;
		ft_find_player(&data);
		data.win = mlx_new_window(data.mlx, data.win_hor, data.win_vert, "cub");
		ft_draw_ray(&data);
		mlx_hook(data.win, 17, 0, &exit_hook, &data);
		mlx_hook(data.win, 2, 0, key_hook, &data);
		mlx_loop(data.mlx);
	}
	return (0);
}

/*
если объявить mlx в структуре lvl или all, то будет утечка на [98304]
если объявить mlx просто в main(), утечки нет
*/
