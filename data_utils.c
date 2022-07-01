#include "cub.h"

void ft_find_player(struct s_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (data->map[i][j] == 'N' || data->map[i][j] == 'S' || \
				data->map[i][j] == 'W' || data->map[i][j] == 'E')
			{
				data->pl_x = data->scale * (j + 0.5);
				data->pl_y = data->scale * (i + 0.5);
				if (data->map[i][j] == 'N')
					data->pl_POV = 3 * M_PI / 2;
				else if (data->map[i][j] == 'S')
					data->pl_POV = M_PI / 2;
				else if (data->map[i][j] == 'E')
					data->pl_POV = 0;
				else if (data->map[i][j] == 'W')
					data->pl_POV = M_PI;
				data->pl_FOV_begin = data->pl_POV - M_PI / 4; // + or - ?
				data->pl_FOV_end = data->pl_POV + M_PI / 4;
			}
			j++;
		}
		i++;
	}
}

// void ft_put_pixel_scale(struct s_data *data, float i, float j, int color)
// {
// 	int x;
// 	int y;

// 	x = j * data->scale;
// 	while(x < data->scale * (j + 1))
// 	{
// 		y = i * data->scale;
// 		while(y < data->scale * (i + 1))
// 		{
// 			mlx_pixel_put(data->mlx, data->win, x, y, color);
// 			y++;
// 		}
// 		x++;
// 	}
// }

void draw_column(struct s_data *data, float ray_len, int j, float angle)
{
	(void) angle;
	float start = (data->win_vert_size / 2) - data->scale * data->win_vert_size / ray_len;
	float finish = (data->win_vert_size / 2) + data->scale * data->win_vert_size / ray_len;
	// printf("\n");
	// printf("pov - %f\n", data->pl_POV);
	// printf("pl_x - %f\n", data->pl_x/64);
	// printf("pl_y - %f\n", data->pl_y/64);
	// printf("FOV_b - %f\n", data->pl_FOV_begin);
	// printf("FOV_e - %f\n", data->pl_FOV_end);
	// printf("start - %f\n", start);
	// printf("finish - %f\n", finish);

	while ((int) start < (int) finish)
	{
		if(j % 64 == 0)
		{
			while(start < finish)
			{
			// mlx_put_image_to_window(data->mlx, data->win, data->all->lvl->no1->img, j, start);
			start+=64;
			}	// mlx_pixel_put(data->mlx, data->win, j, start, 0x00FFFFFF);
		}
		else
		{
			// mlx_put_image_to_window(data->mlx, data->win, data->all->lvl->no1->try, j, start);
			mlx_pixel_put(data->mlx, data->win, j, start, 0x99008000);
			start++;
		}
	}
}

void ft_draw_ray(struct s_data *data)
{
	float x_tmp;
	float y_tmp;
	float ray_len;
	float POV_tmp;
	int j = 0;
	
	POV_tmp = data->pl_FOV_begin; //check begin and end
	while(j < data->win_hor_size)
	{
		x_tmp = data->pl_x;
		y_tmp = data->pl_y;
		while(data->map[(int)(y_tmp/data->scale)][(int)(x_tmp/data->scale)] != '1')
		{
			x_tmp += cos(POV_tmp); // по клеткам?
			y_tmp += sin(POV_tmp);
		}
		if(j == 0 || j == data->win_hor_size - 1)
		{
		printf("x_wall = %d, y_wall = %d\n", (int)x_tmp/64, (int)y_tmp/64);
		printf("x_coor = %f, y_coor = %f\n", fmod(x_tmp, 64), fmod(y_tmp, 64));
		}
		ray_len = sqrt(pow((data->pl_y - y_tmp), 2) + pow((data->pl_x - x_tmp), 2)); // долго!!
		ray_len *= cos(data->pl_POV - POV_tmp);
		POV_tmp += (data->pl_FOV_end - data->pl_FOV_begin) / data->win_hor_size; // 90/848
		draw_column(data, ray_len, j, POV_tmp);
		j++;
	}
	// printf("ray_len END\n");
	// printf("number of rays = %d\n", j);
}

int	exit_hook(struct s_data *data)
{
	mlx_destroy_window(data->mlx, data->win);
	free_all(data->all);
	exit(0);
	return (0);
}

void ft_move(struct s_data *data, char dest)
{
	if (dest == 'W')
	{
		data->pl_x += 10*cos(data->pl_POV);
		data->pl_y += 10*sin(data->pl_POV);
		if (data->map[(int)(data->pl_y/data->scale)][(int)(data->pl_x/data->scale)] == '1')
		{
			data->pl_x -= 10*cos(data->pl_POV);
			data->pl_y -= 10*sin(data->pl_POV);
		}
	}
	else if (dest == 'S')
	{
		data->pl_x -= 10*cos(data->pl_POV);
		data->pl_y -= 10*sin(data->pl_POV);
		if (data->map[(int)(data->pl_y/data->scale)][(int)(data->pl_x/data->scale)] == '1')
		{
			data->pl_x += 10*cos(data->pl_POV);
			data->pl_y += 10*sin(data->pl_POV);
		}
	}
	else if (dest == 'A')
	{
		data->pl_x += 10*cos((M_PI / 2) - data->pl_POV);
		data->pl_y -= 10*sin((M_PI / 2) - data->pl_POV);
		if (data->map[(int)(data->pl_y/data->scale)][(int)(data->pl_x/data->scale)] == '1')
		{
			data->pl_x -= 10*cos((M_PI / 2) - data->pl_POV);
			data->pl_y += 10*sin((M_PI / 2) - data->pl_POV);
		}
	}
	else if (dest == 'D')
	{
		data->pl_x -= 10*cos((M_PI / 2) - data->pl_POV);
		data->pl_y += 10*sin((M_PI / 2) - data->pl_POV);
		if (data->map[(int)(data->pl_y/data->scale)][(int)(data->pl_x/data->scale)] == '1')
		{
			data->pl_x += 10*cos((M_PI / 2) - data->pl_POV);
			data->pl_y -= 10*sin((M_PI / 2) - data->pl_POV);
		}
	}
	else if (dest == 'l')
	{
		data->pl_POV -= 0.1;
		data->pl_FOV_begin = data->pl_POV - M_PI / 4;
		data->pl_FOV_end = data->pl_POV + M_PI / 4;
	}
	else if (dest == 'r')
	{
		data->pl_POV += 0.1;
		data->pl_FOV_begin = data->pl_POV - M_PI / 4;
		data->pl_FOV_end = data->pl_POV + M_PI / 4;
	}
}

int	key_hook(int key_code, struct s_data *data)
{
	mlx_clear_window(data->mlx, data->win);
	if (key_code == 13)
		ft_move(data, 'W');
	if (key_code == 1)
		ft_move(data, 'S');
	if (key_code == 0)
		ft_move(data, 'A');
	if (key_code == 2)
		ft_move(data, 'D');
	if (key_code == 123)
		ft_move(data, 'l');
	if (key_code == 124)
		ft_move(data, 'r');
	if (key_code == 53)
		exit_hook(data);
	//ft_draw_map(data);
	ft_draw_ray(data);
	return (0);
}