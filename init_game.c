#include "cub.h"

float	find_pov(char c)
{
	if (c == 'N')
		return (3 * M_PI / 2);
	else if (c == 'S')
		return (M_PI / 2);
	else if (c == 'E')
		return (0);
	else
		return (M_PI);
}

void	ft_find_player(t_data *data)
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
				data->pl_pov = find_pov(data->map[i][j]);
			}
			j++;
		}
		i++;
	}
}

int	exit_hook(t_data *data)
{
	mlx_destroy_window(data->mlx, data->win);
	free_all(data->all);
	exit(0);
	return (0);
}

int	key_hook(int key_code, t_data *data)
{
	mlx_clear_window(data->mlx, data->win);
	if (key_code == 13)
		ft_move_u_d(data, 'W');
	if (key_code == 1)
		ft_move_u_d(data, 'S');
	if (key_code == 0)
		ft_move_l_r(data, 'A');
	if (key_code == 2)
		ft_move_l_r(data, 'D');
	if (key_code == 123)
		ft_turn_l_r(data, 'l');
	if (key_code == 124)
		ft_turn_l_r(data, 'r');
	if (key_code == 53)
		exit_hook(data);
	ft_draw_ray(data);
	return (0);
}
