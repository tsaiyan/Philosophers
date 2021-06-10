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

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_isdigit(int c)
{
	if (c < 48 || c > 57)
		return (0);
	return (1);
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
		return (0);
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
	}
	return ((int)res * sign);
}

// calloc with exit protection

void	*ft_calloc(int size, int len)
{
	void	*str;
	int		total_size;

	str = malloc((size * len));
	if (!str)
		exit(errno);
	total_size = size * len;
	while (total_size)
		((char *)str)[total_size--] = 0;
	return (str);
}
