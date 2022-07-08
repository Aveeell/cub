/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoch <mkoch@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 13:05:24 by mkoch             #+#    #+#             */
/*   Updated: 2022/07/08 13:05:25 by mkoch            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	rot_left_m(t_data *data)
{
	int	i;

	i = 0;
	while (i < 5)
	{
		data->pl_pov -= data->turn / 5;
		if (data->pl_pov > (-1) * M_PI * 2)
			data->pl_pov = data->pl_pov + 2 * M_PI;
		i++;
	}
}

void	rot_right_m(t_data *data)
{
	int	i;

	i = 0;
	while (i < 5)
	{
		data->pl_pov += data->turn / 5;
		if (data->pl_pov > M_PI * 2)
			data->pl_pov = data->pl_pov - 2 * M_PI;
		i++;
	}
}

int	mouse_toogle(int keycode, int x, int y, t_data *data)
{
	(void)keycode;
	(void)x;
	(void)y;
	if (0 == data->toogle_mouse)
		data->toogle_mouse = 1;
	else
		data->toogle_mouse = 0;
	return (0);
}

int	mouse_move(int x, int y, t_data *data)
{
	(void)y;
	data->x_mouse_before = data->x_mouse_now;
	if (data->toogle_mouse)
	{
		data->x_mouse_now = x;
		if (data->x_mouse_now < data->x_mouse_before)
			rot_left_m(data);
		else if (data->x_mouse_now > data->x_mouse_before)
			rot_right_m(data);
	}
	return (0);
}
