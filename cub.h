#ifndef CUB_H
# define CUB_H

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include "gnl/get_next_line.h"

typedef struct s_textures
{
	char *no;
	char *so;
	char *we;
	char *ea;
	char *fl;
	char *ceil;
	int *fl_rgb;
	int *ceil_rgb;
}				t_textures;

char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_substr(char const *s, int start, int len);
int		ft_strncmp(const char *s1, const char *s2, int n);
int		ft_atoi(const char *str);

int check_map(char **map);
void error(char **map, int i, int j, char *where);
void get_struct(char **tex_raw, t_textures *tex);

char **get_only_map(char **map_raw);
char **get_textures(char **map_raw);
char **get_map(char *map_file);



#endif