#include "cub.h"


void ft_put_pixel(t_data *data, float i, float j, int color)
{
	int x;
	int y;

	x = j * data->scale_minimap;
	while(x < data->scale_minimap * (j + 1))
	{
		y = i * data->scale_minimap;
		while(y < data->scale_minimap * (i + 1))
		{
			put_pixel(data->draw, x, y, color);
			y++;
		}
		x++;
	}
}

void ft_draw_player(t_data *data, float i, float j, int color)
{
	int x;
	int y;

	x = j * data->scale_minimap - 2;
	while(x < j * data->scale_minimap + 2)
	{
		y = i * data->scale_minimap - 2;
		while(y < i * data->scale_minimap + 2)
		{
			put_pixel(data->draw, x + 0.5 * data->scale_minimap, y + 0.5 * data->scale_minimap, color);
			y++;
		}
		x++;
	}
}

void ft_draw_minimap(t_data *data)
{
	int i = 0;
	int j = 0;

	while(data->map[i])
	{
		j = 0;
		while(data->map[i][j])
		{
			if (data->map[i][j] == '1')
				ft_put_pixel(data, i, j, 0x00FF0000);
			else if (data->map[i][j] == ' ')
				ft_put_pixel(data, i, j, 0x000066FF);
			else
				ft_put_pixel(data, i, j, 0xFF000000);
			j++;
		}
		i++;
	}
	//mlx_pixel_put(data->mlx, data->win, data->pl_x, data->pl_y, 0x00FF0000);
	// printf("y = %f\n", (data->pl_y/data->scale) - 0.5);
	// printf("x = %f\n", (data->pl_x/data->scale) - 0.5);
	ft_draw_player(data, (data->pl_y/data->scale) - 0.5, (data->pl_x/data->scale) - 0.5, 0x00FFFF00);
	// printf("here\n");
	// ft_draw_ray(data);
	// ft_put_pixel_scale(data, data->pl_y/data->scale, data->pl_x/data->scale, 0x00FFFF00, scale);
}