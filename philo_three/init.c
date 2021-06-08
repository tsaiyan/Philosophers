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
	int i;

	i = -1;
	sem_unlink("/output");
	sem_unlink("/forks");
	sem_unlink("/eat_count");
	sem_unlink("/stop");
	errno = 0;
	s->forks = sem_open("/forks", O_CREAT, 0666, s->philo_count);
	if (errno)
		ft_exit("can't create semaphore for forks");
	s->output = sem_open("/output", O_CREAT, 0666, 1);
	if (errno)
		ft_exit("semaphore output init error");
	s->stop = sem_open("/stop", O_CREAT, 0666, 1);
	if (errno)
		ft_exit("semaphore someone_died init error");
	s->sem_eat_count = sem_open("/sem_eat_count", O_CREAT, 0666, 0);
	if (errno)
		ft_exit("semaphore eat_count init error");
	return (0);
}

int	create_processes(t_s *s)
{
	int		i;
	pid_t	pid;

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
		pid = fork();
		if (pid == 0)
		{
			if (pthread_create(&s->philos[i].thread, NULL, &hara_kiri, \
							   (void *)&s->philos[i]) != 0)
				ft_exit("pthread_create error");
			life(&s->philos[i]);
			exit(0);
		}
		s->pid_array[i] = pid;
		i++;
	}
	if (pthread_create(&s->finish_eat.thread, NULL, &wait_eat_finish, (void *)s) != 0)
		ft_exit("pthread_create error");
	return (0);
}
