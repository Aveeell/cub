#include "cub.h"

int check_struct(char *str)
{
	if(str)
		error(0,0,0,"check_tex_in_struct");
	return 1;
}

void check_color(char *str, int *arr)
{
	int i;
	int j;

	i = 1;
	j = 0;
	while(str[i])
	{
		while(str[i] == ' ')
			i++;
		if(str[i] < '0' || str[i] > '9')
			error(0,0,0, "check_color");
		else
		{
			arr[j] = ft_atoi(&str[i]);
			while(str[i] >= '0' && str[i] <= '9')
				i++;
			if(str[i] == ',')
			i++;
		}
		j++;
	}
	if(j != 3 || str[ft_strlen(str) - 1] == ',')
		error(0,0,0,"wrong value of rgb");
	while(j--)
		if(arr[j] > 255 || arr[j] < 0)
			error(0,0,0,"check_color out of range");
}

void get_struct(char **tex_raw, t_textures *tex)
{
	int i;
	char *str;
	
	i = 0;
	while(tex_raw[i])
	{
		str = ft_strtrim(tex_raw[i], " ");
		if(!ft_strncmp(str, "NO ", 3) && check_struct(tex->no))
			tex->no = ft_strdup(str, 0);
		else if(!ft_strncmp(str, "SO ", 3) && check_struct(tex->so))
			tex->so = ft_strdup(str, 0);
		else if(!ft_strncmp(str, "WE ", 3) && check_struct(tex->we))
			tex->we = ft_strdup(str, 0);
		else if(!ft_strncmp(str, "EA ", 3) && check_struct(tex->ea))
			tex->ea = ft_strdup(str, 0);
		else if(!ft_strncmp(str, "F ", 2) && check_struct(tex->fl))
			tex->fl = ft_strdup(str, 0);
		else if(!ft_strncmp(str, "C ", 2) && check_struct(tex->ceil))
			tex->ceil = ft_strdup(str, 0);
		else
		{
			free(str);
			error(tex_raw, i, 0, "get_struct wrong symbol");
		}
		i++;
		free(str);
	}
	if (!tex->no || !tex->so || !tex->we || !tex->ea || !tex->fl ||
		!tex->ceil)
			error(0,0,0,"get_struct no textures");
	check_color(tex->fl, tex->fl_rgb);
	check_color(tex->ceil, tex->ceil_rgb);
}