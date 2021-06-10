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

// kill all dauchers pids

void	kill_pid(t_s *s)
{
	int	i;

	i = 0;
	while (s->pid_array[++i])
		kill(s->pid_array[i], SIGKILL);
	sem_unlink("/forks");
	sem_unlink("/output");
	sem_unlink("/stop");
	sem_unlink("/sem_eat_count");
}

// usleep in miliseconds

void	my_usleep(long wait)
{
	long	time;

	time = get_time();
	while (get_time() - time < wait)
		usleep(100);
}

// get now time in miliseconds

long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((long)time.tv_sec * 1000 + (long)time.tv_usec / 1000);
}

// printer with semaphore
// semaphore for extra protection output when one of philos is dead

void	semaphored_print(t_s *s, char *str, int id)
{
	long	time;

	time = get_time() - s->start_time;
	sem_wait(s->output);
	printf("%lu %d %s \n", time, id, str);
	sem_post(s->output);
}
