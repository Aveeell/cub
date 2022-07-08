/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoch <mkoch@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 13:07:12 by mkoch             #+#    #+#             */
/*   Updated: 2022/07/08 13:07:13 by mkoch            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int	ft_atoi(const char *str)
{
	int					i;
	int					neg;
	unsigned long long	res;

	i = 0;
	res = 0;
	neg = 1;
	while ((str[i] >= '\t' && str[i] <= '\r') || str[i] == ' ')
		i++;
	if (str[i] == '-')
		neg = -1;
	if (neg == -1 || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = (res * 10) + (str[i] - '0');
		i++;
	}
	return ((int)res * neg);
}
