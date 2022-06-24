#ifndef CUB_H
# define CUB_H

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include "gnl/get_next_line.h"
# include <mlx.h>

typedef struct s_tex
{
	char *no;
	char *so;
	char *we;
	char *ea;
	char *fl;
	char *ceil;
	int *fl_rgb;
	int *ceil_rgb;
}				t_tex;

typedef struct s_raw
{
	char **map_raw;
	char **tex_raw;
}			t_raw;

typedef struct s_lvl
{
	char **map;
	void *mlx;
	void *win;
	void *no;
	void *so;
	void *we;
	void *ea;
	int fl;
	int ceil;
}				t_lvl;

typedef struct s_all
{
	t_lvl *lvl;
	t_raw *raw;
	t_tex *tex;
}				t_all;

char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_substr(char const *s, int start, int len);
int		ft_strncmp(const char *s1, const char *s2, int n);
int		ft_atoi(const char *str);

int check_map(t_all *all, char **map);
void error(t_all *all, char *where);
void get_struct(t_all *all, char **tex_raw, t_tex *tex);

char **get_only_map(t_all *all, char **map_raw);
char **get_textures(t_all *all, char **map_raw);
char **get_map(char *map_file);

int check_split(char const *s, char c);

#endif