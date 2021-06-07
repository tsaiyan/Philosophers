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

void	mutexed_print(t_s *s, char *str, int id)
{
	long time = get_time() - s->start_time;
	if (!s->exit)
	{
		pthread_mutex_lock(&s->output);
		printf("%lu %d %s \n", time, id, str);
		pthread_mutex_unlock(&s->output);
	}
}

int	drop_forks(t_s *s, t_philo *philo, int id)
{
	if (pthread_mutex_unlock(&s->forks[s->philos[id].left_hand]) == 0)
		mutexed_print(s, "has drop a left fork.", id);
	if (pthread_mutex_unlock(&s->forks[s->philos[id].right_hand]) == 0)
		mutexed_print(s, "has drop a right fork.", id);
	if (s->min_2_eat)
		if (s->philos[id].eat_count == 0)
		{
			s->philos[id].finish_eat = 1;
			return (1);
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
	s->philos[id].eating = 1;
	my_usleep(s->time_4_eat);
	s->philos[id].time_zero = get_time();
	s->philos[id].eating = 0;
}

void	life(void *all)
{
	t_s		*s;
	int		i;
	int		id;

	i = 1;
	s = (t_s *)all;
	id = s->philo_id;
	s->philos[id].time_zero = get_time();
	while (!s->exit)
	{
		if (pthread_mutex_lock(&s->forks[s->philos[id].left_hand]) == 0)
		{
			eat(s, id);
			if (drop_forks(s, &s->philos[id], id) == 1)
				return ;
		}
	}
}

int		all_eated(t_s *s)
{
	int sum;
	int i;

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

void	spy_func(t_s *s)
{
	int i = 0;
	long time;
	long now;

	while (!s->exit)
	{
		i = 1;
		while (i < s->philo_count)
		{
			now = get_time();
			if (now - s->philos[i].time_zero > s->time_2_die && !s->philos[i].eating)
			{
				time = now - s->start_time;
				pthread_mutex_lock(&s->output);
				printf("%lu %d is dead.\n", time, i);
				mutex_destroy(s);
				s->exit = 1;
			}
			if (all_eated(s))
			{
				mutex_destroy(s);
				s->exit = 1;
				exit(0);
			}
			i++;
		}
	}
}
