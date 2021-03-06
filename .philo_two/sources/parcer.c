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

int	parcer(t_s *s)
{
	if (s->a_r_g_c > 6 || s->a_r_g_c < 5)
		ft_exit("bad argv");
	s->philo_count = (int)ft_atoi(s->argv[1]);
	if (s->philo_count > 200)
		ft_exit("too much philosophers");
	if (s->philo_count < 2)
		ft_exit("too little philosophers");
	s->time_2_die = ft_atoi(s->argv[2]);
	s->time_4_eat = ft_atoi(s->argv[3]);
	s->time_4_sleep = ft_atoi(s->argv[4]);
	if (s->time_2_die * s->time_4_eat * s->time_4_sleep <= 0)
		ft_exit("bad arguments");
	if (s->argv[5] != NULL)
	{
		s->min_2_eat = ft_atoi(s->argv[5]);
		if (s->min_2_eat == 0)
			ft_exit("symbol / zero in min eat");
		if (s->min_2_eat < 0)
			ft_exit("bad min eat");
	}
	return (0);
}
