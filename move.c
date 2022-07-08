/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoch <mkoch@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 13:05:28 by mkoch             #+#    #+#             */
/*   Updated: 2022/07/08 13:56:52 by mkoch            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	ft_move_u_d(t_data *data, char dest)
{
	float	delta_x;
	float	delta_y;

	delta_x = data->step * cos(data->pl_pov);
	delta_y = data->step * sin(data->pl_pov);
	if (dest == 'W')
	{
		if (!(data->map[(int)(data->pl_y / data->scale)] \
			[(int)((data->pl_x + delta_x) / data->scale)] == '1'))
			data->pl_x += delta_x;
		if (!(data->map[(int)((data->pl_y + delta_y) / data->scale)] \
			[(int)(data->pl_x / data->scale)] == '1'))
			data->pl_y += delta_y;
	}
	else if (dest == 'S')
	{
		if (!(data->map[(int)(data->pl_y / data->scale)] \
			[(int)((data->pl_x - delta_x) / data->scale)] == '1'))
		data->pl_x -= delta_x;
		if (!(data->map[(int)((data->pl_y - delta_y) / data->scale)] \
			[(int)(data->pl_x / data->scale)] == '1'))
		data->pl_y -= delta_y;
	}
}

void	ft_move_l_r(t_data *data, char dest)
{
	float	delta_x;
	float	delta_y;

	delta_x = data->step * cos((M_PI / 2) - data->pl_pov);
	delta_y = data->step * sin((M_PI / 2) - data->pl_pov);
	if (dest == 'A')
	{
		if (!(data->map[(int)(data->pl_y / data->scale)] \
			[(int)((data->pl_x + delta_x) / data->scale)] == '1'))
			data->pl_x += delta_x;
		if (!(data->map[(int)((data->pl_y - delta_y) / data->scale)] \
			[(int)(data->pl_x / data->scale)] == '1'))
			data->pl_y -= delta_y;
	}
	else if (dest == 'D')
	{
		if (!(data->map[(int)(data->pl_y / data->scale)] \
			[(int)((data->pl_x - delta_x) / data->scale)] == '1'))
			data->pl_x -= delta_x;
		if (!(data->map[(int)((data->pl_y + delta_y) / data->scale)] \
			[(int)(data->pl_x / data->scale)] == '1'))
			data->pl_y += delta_y;
	}
}

void	ft_turn_l_r(t_data *data, char dest)
{	
	if (dest == 'l')
		data->pl_pov -= data->turn;
	else if (dest == 'r')
		data->pl_pov += data->turn;
}
