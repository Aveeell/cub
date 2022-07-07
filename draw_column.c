#include "cub.h"

unsigned int	get_pixel(t_data *data, unsigned x, unsigned y)
{
	return (*(unsigned *)(data->cur_wall->addr + \
	(y * data->cur_wall->l_len + x * (data->cur_wall->bpp / 8))));
}

void	put_pixel(t_img *draw, int x, int y, unsigned int color)
{
	char	*dst;

	dst = draw->addr + (y * draw->l_len + x * (draw->bpp / 8));
	*(unsigned *)dst = color;
}

float	get_delta(t_data *data, float x, float y)
{
	x = x / data->scale;
	y = y / data->scale;
	if (data->map[(int)(y)][(int)(x + 0.001f)] != '1')
	{
		data->cur_wall = data->we;
		return (((float)(int)y + 1.0f) - y);
	}
	if (data->map[(int)(y + 0.001f)][(int)(x)] != '1')
	{
		data->cur_wall = data->no;
		return (x - (float)(int)x);
	}
	if (data->map[(int)(y)][(int)(x - 0.001f)] != '1')
	{
		data->cur_wall = data->ea;
		return (y - (float)(int)y);
	}
	if (data->map[(int)(y - 0.001f)][(int)(x)] != '1')
	{
		data->cur_wall = data->so;
		return (((float)(int)x + 1.0f) - x);
	}
	data->cur_wall = data->we;
	return (0.0f);
}

void	get_values(t_data *data, long double *start, long double *finish,
					long double *col_h)
{
	*col_h = data->win_h / (data->len / data->scale);
	*start = (data->win_h - *col_h) / 2;
	*finish = data->win_h - (data->win_h - *col_h) / 2;
	if (*start < 0)
		*start = 0;
	if (*finish > data->win_h)
		*finish = data->win_h;
}

void	draw_column(t_data *data, int j, float x, float y)
{
	int			i;
	long double	start;
	long double	finish;
	long double	col_h;
	float		delta_y;

	i = 0;
	get_values(data, &start, &finish, &col_h);
	while (i < (int) start)
		put_pixel(data->draw, j, i++, data->ceil);
	while (i <= (int) finish)
	{
		delta_y = (i - (data->win_h - col_h) / 2) / col_h;
		if (delta_y < 0)
			delta_y = 0;
		else if (delta_y > 1)
			delta_y = 1;
		put_pixel(data->draw, j, i, get_pixel(data, data->scale * \
			get_delta(data, x, y), data->scale * delta_y));
		i++;
	}
	while (i < data->win_h)
		put_pixel(data->draw, j, i++, data->fl);
}
