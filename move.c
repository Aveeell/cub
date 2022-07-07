#include "cub.h"

void	ft_move_u_d(t_data *data, char dest)
{
	if (dest == 'W')
	{
		data->pl_x += data->step * cos(data->pl_pov);
		data->pl_y += data->step * sin(data->pl_pov);
		if (data->map[(int)(data->pl_y / data->scale)] \
			[(int)(data->pl_x / data->scale)] == '1')
		{
			data->pl_x -= data->step * cos(data->pl_pov);
			data->pl_y -= data->step * sin(data->pl_pov);
		}
	}
	else if (dest == 'S')
	{
		data->pl_x -= data->step * cos(data->pl_pov);
		data->pl_y -= data->step * sin(data->pl_pov);
		if (data->map[(int)(data->pl_y / data->scale)] \
			[(int)(data->pl_x / data->scale)] == '1')
		{
			data->pl_x += data->step * cos(data->pl_pov);
			data->pl_y += data->step * sin(data->pl_pov);
		}
	}
}

void	ft_move_l_r(t_data *data, char dest)
{
	if (dest == 'A')
	{
		data->pl_x += data->step * cos((M_PI / 2) - data->pl_pov);
		data->pl_y -= data->step * sin((M_PI / 2) - data->pl_pov);
		if (data->map[(int)(data->pl_y / data->scale)] \
			[(int)(data->pl_x / data->scale)] == '1')
		{
			data->pl_x -= data->step * cos((M_PI / 2) - data->pl_pov);
			data->pl_y += data->step * sin((M_PI / 2) - data->pl_pov);
		}
	}
	else if (dest == 'D')
	{
		data->pl_x -= data->step * cos((M_PI / 2) - data->pl_pov);
		data->pl_y += data->step * sin((M_PI / 2) - data->pl_pov);
		if (data->map[(int)(data->pl_y / data->scale)] \
			[(int)(data->pl_x / data->scale)] == '1')
		{
			data->pl_x += data->step * cos((M_PI / 2) - data->pl_pov);
			data->pl_y -= data->step * sin((M_PI / 2) - data->pl_pov);
		}
	}
}

void	ft_turn_l_r(t_data *data, char dest)
{	
	if (dest == 'l')
		data->pl_pov -= data->turn;
	else if (dest == 'r')
		data->pl_pov += data->turn;
}
