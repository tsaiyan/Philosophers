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

int	ft_eat(t_s *s, t_philo *philo)
{
	sem_wait(s->forks);
	semaphored_print(s, "has taken a fork", philo->id);
	sem_wait(s->forks);
	semaphored_print(s, "has taken a fork", philo->id);
	my_usleep(s->time_4_eat);
	semaphored_print(s, "is eating", philo->id);
	philo->eat_count--;
	philo->time_last_eat = get_time();
	return (0);
}

void	ft_philos_ate(t_s *s, t_philo *philo)
{
	if (s->min_2_eat)
	{
		if (philo->eat_count <= 0)
		{
			sem_post(s->sem_eat_count);
			exit(0);
		}
	}
}

int	ft_drop_forks(t_s *s, t_philo *philo)
{
	sem_post(s->forks);
	sem_post(s->forks);
	ft_philos_ate(s, philo);
	semaphored_print(s, "is sleeping", philo->id);
	my_usleep(s->time_4_sleep);
	semaphored_print(s, "is thinking", philo->id);
	return (0);
}

void	life(t_philo *philo)
{
	int	flag;
	t_s	*s;

	s = (t_s *)philo->all;
	flag = 1;
	if (philo->id % 2 == 0)
		my_usleep(80);
	while (flag)
	{
		ft_eat(s, philo);
		ft_drop_forks(s, philo);
	}
	exit(0);
}
