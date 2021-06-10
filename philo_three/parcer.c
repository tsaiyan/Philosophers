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

// find chars in argv

int	check_chars_in_argv(t_s *s)
{
	int	i;
	int	j;

	i = 1;
	while (s->argv[i])
	{
		j = 0;
		while (s->argv[i][j])
		{
			if (!ft_isdigit(s->argv[i][j]))
				ft_exit("char in argv");
			j++;
		}
		i++;
	}
	return (0);
}

// checks for:
// 2 > philos > 200
// zeroes in argv

int	parcer(t_s *s)
{
	if (s->a_r_g_c > 6 || s->a_r_g_c < 5)
		ft_exit("bad argv");
	s->philo_count = (int)ft_atoi(s->argv[1]);
	if (s->philo_count > 200)
		ft_exit("too much philosophers");
	if (s->philo_count < 2)
		ft_exit("too little philosophers");
	check_chars_in_argv(s);
	s->time_2_die = ft_atoi(s->argv[2]);
	s->time_4_eat = ft_atoi(s->argv[3]);
	s->time_4_sleep = ft_atoi(s->argv[4]);
	if (s->time_2_die * s->time_4_eat * s->time_4_sleep <= 0)
		ft_exit("bad arguments");
	if (s->argv[5] != NULL)
	{
		s->min_2_eat = ft_atoi(s->argv[5]);
		if (s->min_2_eat == 0)
			ft_exit("zero in min eat");
		if (s->min_2_eat < 0)
			ft_exit("bad min eat");
	}
	return (0);
}
