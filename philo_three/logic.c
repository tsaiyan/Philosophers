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

int	drop_forks(t_s *s, t_philo *philo, int id)
{
	sem_post(s->forks);
	semaphored_print(s, "has drop a fork.", id);
	sem_post(s->forks);
	semaphored_print(s, "has drop a fork.", id);
	s->philos[id].eat_count--;
	if (s->min_2_eat && philo->eat_count <= 0)
	{
		sem_post(s->sem_eat_count);
		exit(0);
	}
	semaphored_print(s, "is sleeping.", id);
	my_usleep(s->time_4_sleep);
	semaphored_print(s, "is thinking.", id);
	return (0);
}

void	eat(t_s *s, int id)
{
	sem_wait(s->forks);
	semaphored_print(s, "has take a fork.", id);
	sem_wait(s->forks);
	semaphored_print(s, "has take a fork.", id);
	semaphored_print(s, "is eating.", id);
	my_usleep(s->time_4_eat);
	s->philos[id].time_last_eat = get_time();
	s->philos[id].time_zero = get_time();
}

// life func of philos

void	*life(t_philo	*philo)
{
	t_s		*s;

	s = (t_s *)philo->all;
	philo->time_zero = get_time();
	if (philo->id % 2 == 0)
		my_usleep(s->time_4_eat);
	while (1)
	{
		eat(s, philo->id);
		drop_forks(s, philo, philo->id);
		usleep(100);
	}
}

// check if is eat counter and exit when all philo are eat

int	all_eated(t_s *s)
{
	int	sum;
	int	i;

	i = 1;
	sum = 0;
	while (i <= s->philo_count)
	{
		if (s->philos[i].finish_eat)
			sum++;
		i++;
	}
	if (sum == s->philo_count)
		return (1);
	return (0);
}

// check eat count in each thread
// dead report

void	*wait_eat_finish(void *all)
{
	int i;
	t_s *s;

	s = (t_s *)all;
	i = -1;
	my_usleep(s->time_4_eat);
	while(++i < s->philo_count)
	{
		sem_wait(s->sem_eat_count);
		usleep(100);
	}
	sem_post(s->stop);
	return (NULL);
}

void	*hara_kiri(void *void_philo)
{
	int	i;
	t_s	*s;
	t_philo *philo;

	philo = (t_philo *)void_philo;
	s = (t_s *)philo->all;
	i = philo->id;
	my_usleep(s->time_2_die);
	while (1)
	{
		if (get_time() - philo->time_zero > s->time_2_die)
		{
			sem_wait(s->output);
			printf("%lu %d is dead.\n", get_time() - s->start_time, i);
			sem_post(s->stop);
			exit(0);
		}
	}
	return (NULL);
}
