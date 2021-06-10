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
	sem_unlink("/output");
	sem_unlink("/forks");
	sem_unlink("/sem_eat_count");
	sem_unlink("/stop");
	errno = 0;
	s->forks = sem_open("/forks", O_CREAT, 0666, s->philo_count);
	if (errno)
		ft_exit("can't create semaphore for forks");
	s->output = sem_open("/output", O_CREAT, 0666, 1);
	if (errno)
		ft_exit("semaphore output init error");
	s->stop = sem_open("/stop", O_CREAT, 0666, 0);
	if (errno)
		ft_exit("semaphore someone_died init error");
	s->sem_eat_count = sem_open("/sem_eat_count", O_CREAT, 0666, 0);
	if (errno)
		ft_exit("semaphore eat_count init error");
	return (0);
}

void	philos_init(t_s *s)
{
	int	i;

	i = 1;
	s->philos = ft_calloc(sizeof(t_philo *), s->philo_count + 1);
	while (i <= s->philo_count)
	{
		s->philos[i] = ft_calloc(sizeof(t_philo), 1);
		s->philos[i]->id = i;
		s->philos[i]->all = s;
		s->philos[i]->eat_count = s->min_2_eat;
		i++;
	}
}

int	create_processes(t_s *s)
{
	int		i;
	pid_t	pid;

	philos_init(s);
	i = 1;
	s->start_time = get_time();
	if (pthread_create(&s->finish_eat, NULL, check_all_ate, \
					(void *)s->philos[i]) != 0)
		ft_exit("can't create pthread for check all ate");
	while (i <= s->philo_count)
	{
		pid = fork();
		if (pid == 0)
		{
			if (pthread_create(&s->philos[i]->thread, NULL, hara_kiri, \
							(void *)s->philos[i]) != 0)
				ft_exit("can't create pthread for hara kiri");
			life(s->philos[i]);
		}
		s->pid_array[i] = pid;
		i++;
	}
	return (0);
}
