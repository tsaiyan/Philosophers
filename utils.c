/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philosophers                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaiyan <tsaiyan@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 19:20:04 by tsaiyan           #+#    #+#             */
/*   Updated: 2021/06/04 19:20:06 by tsaiyan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_exit(char *str)
{
	printf("%s\n", str);
	exit(-1);
}

int	ft_atoi(const char *str)
{
	int			sign;
	long int	i;
	long int	res;

	res = 0;
	i = 0;
	sign = 1;
	if (!str)
		return 0;
	while ((str[i] == 32) || ((str[i] >= 9 && str[i] <= 13)))
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (ft_isdigit(str[i]))
	{
		res = res * 10 + (str[i] - 48);
		i++;
		if (res > 922337203685477580 && sign < 0)
			return (0);
		if (res > 922337203685477580 && sign > 0)
			return (-1);
	}
	return ((int)res * sign);
}

void *ft_calloc(int size, int len)
{
    void *str;

	str = malloc((size * len));
	if (!str)
		exit(errno);
	int total_size = size*len;
	while (total_size)
		((char *)str)[total_size--] = 0;
	return (str);
}
