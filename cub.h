#ifndef CUB_H
# define CUB_H

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include "gnl/get_next_line.h"

char	**ft_split(char const *s, char c);
char	*get_next_line(int fd);
char	*ft_strjoin(char *s1, char *s2);
int	ft_strncmp(const char *s1, const char *s2, int n);
char	*ft_substr(char const *s, int start, int len);
int check_wall(char **map);
void error(char **map, int i, int j, char *where);


#endif