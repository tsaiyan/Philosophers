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

// kill own process when philos is dead by put on exit flag in the sem

void	*hara_kiri(void *void_philo)
{
	t_s		*s;
	t_philo	*philo;
	int		i;
	long	now;

	i = 0;
	philo = (t_philo *)void_philo;
	s = (t_s *)philo->all;
	my_usleep(s->time_2_die);
	now = get_time();
	while (1)
	{
		if (now - philo->time_last_eat >= s->time_2_die)
		{
			sem_wait(s->output);
			printf("%lu %d died\n", now - s->start_time, philo->id);
			sem_post(s->stop);
			break ;
		}
	}
	return (0);
}
