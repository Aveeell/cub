#include "cub.h"

float	ft_find_pov(char c)
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

void	ft_find_player(struct s_data *data)
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
				data->pl_pov = ft_find_pov(data->map[i][j]);
			}
			j++;
		}
		i++;
	}
}

int	exit_hook(t_all *all)
{
	mlx_destroy_window(all->data->mlx, all->data->win);
	mlx_destroy_image(all->data->mlx, all->data->no->img);
	mlx_destroy_image(all->data->mlx, all->data->so->img);
	mlx_destroy_image(all->data->mlx, all->data->we->img);
	mlx_destroy_image(all->data->mlx, all->data->ea->img);
	mlx_destroy_image(all->data->mlx, all->data->draw->img);
	free_all(all);
	exit(0);
	return (0);
}

int	key_hook(int key_code, t_all *all)
{
	if (key_code == 13 || key_code == 126)
		ft_move_u_d(all->data, 'W');
	if (key_code == 1 || key_code == 125)
		ft_move_u_d(all->data, 'S');
	if (key_code == 0)
		ft_move_l_r(all->data, 'A');
	if (key_code == 2)
		ft_move_l_r(all->data, 'D');
	if (key_code == 123)
		ft_turn_l_r(all->data, 'l');
	if (key_code == 124)
		ft_turn_l_r(all->data, 'r');
	if (key_code == 53)
		exit_hook(all);
	return (0);
}

int	render(t_data *data)
{	
	static int	frame = 0;

	if (frame % 4 == 0)
	{
		mlx_clear_window(data->mlx, data->win);
		ft_draw_ray(data);
		ft_draw_minimap(data);
		mlx_put_image_to_window(data->mlx, data->win, data->draw->img, 0, 0);
		frame = 0;
	}
	frame++;
	return (0);
}
