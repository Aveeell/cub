#ifndef CUB_H
# define CUB_H

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include "gnl/get_next_line.h"
# include <mlx.h>

typedef struct s_img
{
	void *img;
	void *try;
	char *try_addr;
	int bits_per_pix;
	int size;
	int end;
	char *addr;
	int color;
}				t_img;

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

typedef struct s_lvl
{
	char	**map;
	void	*mlx;
	void	*win;
	void	*no;
	void	*so;
	void	*we;
	void	*ea;
	int		fl;
	int		ceil;
	t_img	*no1;
}				t_lvl;

typedef struct s_all
{
	t_lvl	*lvl;
	t_raw	*raw;
	t_tex	*tex;
}				t_all;

char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char *s, char c);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_substr(char const *s, int start, int len);
int		ft_strncmp(const char *s1, const char *s2, int n);
int		ft_atoi(const char *str);

void	check_map(t_all *all, char **map);
void	error(t_all *all, char *where);
void	get_struct(t_all *all, char **tex_raw, t_tex *tex);

char	**get_only_map(t_all *all, char **map_raw);
char	**get_textures(t_all *all, char **map_raw);
char	**get_map(char *map_file);

int		check_split(char const *s, char c);

void	fill_lvl_stuct(t_all *all, t_tex *tex, t_lvl *lvl);
t_all	*init_all(void);
void	free_all(t_all *all);

int		get_middle_of_map_file(char **map_raw);
int		get_start_of_map(char **map_raw);
int		get_end_of_map(char **map_raw, int i);
void	check_walls_around_space(t_all *all, char **map);
void	check_all_zeros(t_all *all, char **map);
int	get_color(int t, int r, int g, int b);

//------------------------------------------------------------------------------
#include <math.h>

struct s_data {
	char	**map;
	int		num_rows;
	int		width;
	int		height;
	void	*mlx;
	void	*win;
	float	pl_x;
	float	pl_y;
	float	pl_POV;
	float	pl_FOV_begin;
	float	pl_FOV_end;
	int		scale;
	int		win_hor_size;
	int		win_vert_size;
	t_all	*all;
};

void ft_find_player(struct s_data *data);
void ft_put_pixel_scale(struct s_data *data, float i, float j, int color);
void draw_column(struct s_data *data, float ray_len, int j, float angle);
void ft_draw_ray(struct s_data *data);
int	exit_hook(struct s_data *data);
void ft_move(struct s_data *data, char dest);
int	key_hook(int key_code, struct s_data *data);

//------------------------------------------------------------------------------

#endif
