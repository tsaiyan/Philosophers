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

int	drop_forks(t_s *s, int id)
{
	if (pthread_mutex_unlock(&s->forks[s->philos[id].left_hand]) == 0)
		mutexed_print(s, "has drop a left fork.", id);
	if (pthread_mutex_unlock(&s->forks[s->philos[id].right_hand]) == 0)
		mutexed_print(s, "has drop a right fork.", id);
	if (s->min_2_eat)
	{
		if (s->philos[id].eat_count == 0)
		{
			s->philos[id].finish_eat = 1;
			return (1);
		}
	}
	mutexed_print(s, "is sleeping.", id);
	my_usleep(s->time_4_sleep);
	mutexed_print(s, "is thinking.", id);
	return (0);
}

void	eat(t_s *s, int id)
{
	mutexed_print(s, "has take a left fork.", id);
	pthread_mutex_lock(&s->forks[s->philos[id].right_hand]);
	mutexed_print(s, "has take a right fork.", id);
	mutexed_print(s, "is eating.", id);
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
		if (pthread_mutex_lock(&s->forks[philo->left_hand]) == 0)
		{
			eat(s, philo->id);
			if (drop_forks(s, philo->id) == 1)
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
		mutex_destroy(s);
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
				pthread_mutex_lock(&s->output);
				printf("%lu %d is dead.\n", get_time() - s->start_time, i);
				mutex_destroy(s);
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
