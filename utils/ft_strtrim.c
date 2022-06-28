#include "../cub.h"

static int	ft_is_set(char const *set, char c)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		j;
	char	*s;

	i = 0;
	if (!s1)
		return ((void *)0);
	j = ft_strlen(s1);
	while (s1[i] && ft_is_set(set, s1[i]))
		i++;
	while (j > i && ft_is_set(set, s1[j - 1]))
		j--;
	s = ft_substr(s1, i, j - i);
	return (s);
}
