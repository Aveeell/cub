#include "cub.h"

// int ft_strlen(char *s)
// {
// 	int	i;

// 	i = 0;
// 	while(s[i])
// 		i++;
// 	return (i);
// }

int	ft_strncmp(const char *s1, const char *s2, int n)
{
	int				i;
	unsigned char	*s11;
	unsigned char	*s22;

	i = 0;
	s11 = (unsigned char *)s1;
	s22 = (unsigned char *)s2;
	while (i < n)
	{
		if (s11[i] != s22[i] || (s11[i] == '\0' && s22[i] == '\0'))
			return (s11[i] - s22[i]);
		i++;
	}
	return (0);
}

char	*ft_substr(char const *s, int start, int len)
{
	char	*substr;
	int		j;

	j = 0;
	if (!s)
		return (NULL);
	if (len > ft_strlen(s))
		len = ft_strlen(s);
	substr = malloc(sizeof(char) * len + 1);
	if (!substr)
		return ((void *)0);
	if (start < ft_strlen(s))
	{
		while (len > 0 && s[start] != '\0')
		{
			substr[j++] = s[start++];
			len--;
		}
	}
	substr[j] = '\0';
	return (substr);
}

static char	*ft_join(char *res, char *s, int len)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		res[len + i] = s[i];
		i++;
	}
	res[len + i] = '\0';
	return (res);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*res;
	int		i;
	int		j;
	int		len_strs;

	i = 0;
	j = 0;
	if (!ft_strlen(s1))
		res = ft_strdup(s2, 0);
	else
	{
		len_strs = ft_strlen(s1) + ft_strlen(s2);
		res = malloc((sizeof(char) * len_strs + 1));
		if (!res)
			return ((void *)0);
		res = ft_join(ft_join(res, s1, 0), s2, ft_strlen(s1));
	}
	free(s1);
	return (res);
}