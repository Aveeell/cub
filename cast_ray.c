/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoch <mkoch@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 13:04:29 by mkoch             #+#    #+#             */
/*   Updated: 2022/07/08 13:04:30 by mkoch            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	ft_one_ray(t_data *data, float pov_tmp, int j)
{
	long double	x;
	long double	y;
	float		pov_tmp_sin;
	float		pov_tmp_cos;

	x = data->pl_x;
	y = data->pl_y;
	pov_tmp_sin = sin(pov_tmp);
	pov_tmp_cos = cos(pov_tmp);
	while (data->map[(int)(y / data->scale)][(int)(x / data->scale)] != '1')
	{
		x += pov_tmp_cos / 100;
		y += pov_tmp_sin / 100;
	}
	data->len = sqrtf(powf((data->pl_y - y), 2) + powf((data->pl_x - x), 2));
	data->len *= cosf(data->pl_pov - pov_tmp);
	draw_column(data, j, x, y);
}

void	ft_draw_ray(t_data *data)
{
	float	pov_tmp;
	float	delta_angle;
	int		j;

	j = 0;
	pov_tmp = data->pl_pov - M_PI / 4;
	delta_angle = (M_PI / 2) / data->win_w;
	while (j < data->win_w)
	{
		ft_one_ray(data, pov_tmp, j);
		pov_tmp += delta_angle;
		j++;
	}
}
