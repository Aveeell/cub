#ifndef CUB_H
# define CUB_H

# include <mlx.h>
# include <math.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "gnl/get_next_line.h"

typedef struct s_tex
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	char	*fl;
	char	*ceil;
	int		*fl_rgb;
	int		*cl_rgb;
}				t_tex;

typedef struct s_raw
{
	char	**map_raw;
	char	**tex_raw;
}			t_raw;

typedef struct s_img {
	void	*img;
	char	*addr;
	int		bpp;
	int		l_len;
	int		end;
}				t_img;

typedef struct s_data {
	char	**map;
	void	*mlx;
	void	*win;
	int		step;
	float	turn;
	float	pl_x;
	float	pl_y;
	float	pl_pov;
	int		scale;
	int		win_w;
	int		win_h;
	int		fl;
	int		ceil;
	float	len;
	t_img	*no;
	t_img	*so;
	t_img	*ea;
	t_img	*we;
	t_img	*draw;
	t_img	*cur_wall;
}	t_data;

typedef struct s_all
{
	t_raw	*raw;
	t_tex	*tex;
	t_data	*data;
}				t_all;

char			*ft_strtrim(char const *s1, char const *set);
char			**ft_split(char *s, char c);
char			*ft_strjoin(char *s1, char *s2);
char			*ft_substr(char const *s, int start, int len);
int				ft_strncmp(const char *s1, const char *s2, int n);
int				ft_atoi(const char *str);

void			check_map(t_all *all, char **map);
void			error(t_all *all, char *where);
void			get_struct(t_all *all, char **tex_raw, t_tex *tex);

char			**get_only_map(t_all *all, char **map_raw);
char			**get_textures(t_all *all, char **map_raw);
char			**get_map(char *map_file);

int				check_split(char const *s, char c);

void			fill_lvl_stuct(t_all *all, t_tex *tex, t_data *data);
t_all			*init_all(void);
void			free_all(t_all *all);

int				get_middle_of_map_file(char **map_raw);
int				get_start_of_map(char **map_raw);
int				get_end_of_map(char **map_raw, int i);
void			check_walls_around_space(t_all *all, char **map);
void			check_all_zeros(t_all *all, char **map);

void			ft_find_player(struct s_data *data);
unsigned int	get_pixel(t_data *data, unsigned x, unsigned y);
void			put_pixel(t_img *draw, int x, int y, unsigned int color);
float			get_delta(t_data *data, float x, float y);
void			draw_column(t_data *data, int j, float x, float y);
void			ft_one_ray(t_data *data, float pov_tmp, int j);
void			ft_draw_ray(t_data *data);
int				exit_hook(t_all *all);
void			ft_move_u_d(t_data *data, char dest);
void			ft_move_l_r(t_data *data, char dest);
void			ft_turn_l_r(t_data *data, char dest);
int				key_hook(int key_code, t_all *all);
int				render(t_data *data);
void			run_game(t_data *data, t_all *all);

#endif
