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

void	my_usleep(long wait)
{
	long	time;

	time = get_time();
	while (get_time() - time < wait)
		usleep(100);
}

void	my_sem_destroy(t_s *s)
{
	sem_unlink("forks");
	sem_unlink("output");
}

long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((long)time.tv_sec * 1000 + (long)time.tv_usec / 1000);
}

void	semaphored_print(t_s *s, char *str, int id)
{
	long	time;

	time = get_time() - s->start_time;
	if (!s->exit)
	{
		sem_wait(s->output);
		printf("%lu %d %s \n", time, id, str);
		sem_post(s->output);
	}
}
