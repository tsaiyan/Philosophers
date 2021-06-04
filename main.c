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

void	life(void *all)
{
	t_s		*s;
	t_philo	*philo;
	int		i;

	i = 1;
	s = (t_s *)all;
	philo = &s->philos[s->philo_id];
	usleep(100);
	if (s->philo_id == philo->id)
	{
		pthread_mutex_lock(&s->mutex);
		s->philo_died = philo->id;
		pthread_mutex_unlock(&s->mutex);
	}
	while (1)
	{
		
	}
	return ;
}

void	spy_func(t_s *s)
{
	int flag;

	flag = 1;
	while (flag)
	{
		pthread_mutex_lock(&s->output);
		if (s->philo_died)
		{
			printf("%d is dead.\n", s->philo_died);
			pthread_mutex_destroy(&s->output);
			flag = 0;
		}
		pthread_mutex_unlock(&s->output);
	}
}

int	ft_eat(t_s *s)
{
	return (0);
}

int main(int argc, char **argv)
{
	
	t_s *s;
	s = ft_calloc(sizeof(t_s), 1);
	s->argс = argc;
	s->argv = argv;

	parcer(s);
	pthread_mutex_init(&s->output, NULL);
	pthread_mutex_init(&s->mutex, NULL);
	create_phtreads(s);
	create_forks(s);
	usleep(10000);
	printf("\n");

	return 0;
}
