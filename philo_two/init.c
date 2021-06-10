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

int	init_sem(t_s *s)
{
	int	i;

	i = -1;
	s->forks = sem_open("forks", O_CREAT, 0666, 0);
	if (errno)
		ft_exit("can't create semaphore for forks");
	while (++i < s->philo_count)
	{
		sem_post(s->forks);
		if (errno)
			ft_exit("can't post fors semaphore in init");
	}
	s->output = sem_open("output", O_CREAT, 0666, 0);
	if (errno)
		ft_exit("semaphore output init error");
	sem_post(s->output);
	if (errno)
		ft_exit("output error post in init");
	return (0);
}

int	create_pthreads(t_s *s)
{
	int	i;

	i = 1;
	s->philos = ft_calloc(sizeof(t_philo), s->philo_count);
	s->start_time = get_time();
	while (i <= s->philo_count)
	{
		s->philos[i].id = i;
		s->philos[i].left_hand = i - 1;
		s->philos[i].right_hand = i % s->philo_count;
		s->philos[i].eat_count = s->min_2_eat;
		s->philos[i].all = s;
		if (pthread_create(&s->philos[i].thread, NULL, &life, \
						   (void *)&s->philos[i]) != 0)
			ft_exit("pthread_create error");
		i++;
	}
	if (pthread_create(&s->philos[0].thread, NULL, &spy_func, (void *)s) != 0)
		ft_exit("pthread_create error");
	return (0);
}
