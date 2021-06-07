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

void	mutex_destroy(t_s *s)
{
	int	i;

	i = -1;
	pthread_mutex_destroy(&s->output);
	while (++i <= s->philo_count)
		pthread_mutex_destroy(&s->forks[i]);
}

void	my_usleep(long wait)
{
	long	time;

	time = get_time();
	while (get_time() - time < wait)
		usleep(100);
}

long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((long)time.tv_sec * 1000 + (long)time.tv_usec / 1000);
}

void	mutexed_print(t_s *s, char *str, int id)
{
	long	time;

	time = get_time() - s->start_time;
	if (!s->exit)
	{
		pthread_mutex_lock(&s->output);
		printf("%lu %d %s \n", time, id, str);
		pthread_mutex_unlock(&s->output);
	}
}
