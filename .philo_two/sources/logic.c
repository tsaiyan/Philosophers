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
	(void)philo;
	sem_post(s->forks);
	sem_post(s->forks);
	if (s->min_2_eat)
	{
		if (s->philos[id].eat_count == 0)
		{
			s->philos[id].finish_eat = 1;
			return (1);
		}
	}
	semaphored_print(s, "is sleeping", id);
	my_usleep(s->time_4_sleep);
	semaphored_print(s, "is thinking", id);
	return (0);
}

void	eat(t_s *s, int id)
{
	semaphored_print(s, "has taken a fork", id);
	sem_wait(s->forks);
	semaphored_print(s, "has taken a fork", id);
	semaphored_print(s, "is eating", id);
	s->philos[id].eat_count--;
	my_usleep(s->time_4_eat);
	s->philos[id].time_last_eat = get_time();
	s->philos[id].time_zero = get_time();
}

// life func of philos

void	*life(void *void_philos)
{
	t_philo	*philo;
	t_s		*s;

	philo = (t_philo *)void_philos;
	s = (t_s *)philo->all;
	philo->time_zero = get_time();
	if (philo->id % 2 == 0)
		my_usleep(s->time_4_eat);
	while (!s->exit)
	{
		if (sem_wait(s->forks) == 0)
		{
			eat(s, philo->id);
			if (drop_forks(s, philo, philo->id) == 1)
				return (NULL);
		}
	}
	return (NULL);
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
	{
		s->exit = 1;
		return (1);
	}
	return (0);
}

// checks time life in each thread
// check eat count in each thread
// dead report

void	*spy_func(void *all)
{
	int	i;
	t_s	*s;

	s = (t_s *)all;
	my_usleep(s->time_2_die);
	while (!s->exit)
	{
		i = 1;
		while (i <= s->philo_count)
		{
			if (get_time() - s->philos[i].time_zero > s->time_2_die)
			{
				sem_wait(s->output);
				printf("%lu %d died\n", get_time() - s->start_time, i);
				s->exit = 1;
				return (NULL);
			}
			if (all_eated(s))
				return (NULL);
			i++;
		}
	}
	return (NULL);
}
