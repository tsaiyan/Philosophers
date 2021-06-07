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


int	parcer(t_s *s)
{
	if (s->argс > 6 || s->argс < 5)
		ft_exit("bad argv");
	s->philo_count = (int)ft_atoi(s->argv[1]);
	if (s->philo_count > 200)
		ft_exit("too much philosopthers");
	if (s->philo_count < 2)
		ft_exit("too little philosopthers");
	s->time_2_die = ft_atoi(s->argv[2]);
	s->time_4_eat = ft_atoi(s->argv[3]);
	s->time_4_sleep = ft_atoi(s->argv[4]);
	if (s->time_2_die * s->time_4_eat * s->time_4_sleep <= 0)
		ft_exit("bad arguments");
	if (s->argv[5] != NULL)
	{
		s->min_2_eat = ft_atoi(s->argv[5]);
		if (s->min_2_eat == 0)
			ft_exit("symbol / zero in min eat");
		if (s->min_2_eat < 0)
			ft_exit("bad min eat");
	}
	s->start_time = get_time();
	return (0);
}


int	create_forks(t_s *s)
{
	int i;

	i = -1;
	s->forks = ft_calloc(sizeof(pthread_mutex_t), s->philo_count + 1);
	while (++i < s->philo_count + 1)
		if (pthread_mutex_init(&s->forks[i], NULL) != 0)
			ft_exit("can't create mutex for forks");
	return (0);
}

int	create_pthreads(t_s *s)
{
	int i;

	i = 1;
	s->philos = ft_calloc(sizeof(t_philo), s->philo_count + 1);

	while (i < s->philo_count + 1)
	{
		s->philo_id = i;
		s->philos[i].left_hand = i - 1;
		s->philos[i].right_hand = i % s->philo_count;
		s->philos[i].eat_count = s->min_2_eat;
		if (pthread_create(&s->philos[i], NULL, &life, (void *)s) != 0)
			ft_exit("pthread_create error");
		usleep(100);
		i++;
	}
	if (pthread_create(&s->philos[0], NULL, &spy_func, (void *)s) != 0)
		ft_exit("pthread_create error");
	return (0);
}
