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

#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
 #include <unistd.h>
#include <errno.h>

typedef struct	s_philo
{
	pthread_t	thread;
	int			id;
	int			left_hand;
	int			right_hand;
}				t_philo;

typedef struct	s_s
{
	pthread_mutex_t	output;
	pthread_mutex_t	mutex;
	pthread_mutex_t	*forks;
	int		argс;
	char	**argv;
	
	int		time_4_eat;
	int		time_4_sleep;
	int		time_2_die;
	int		min_2_eat;
	int		philo_count;
	
	int		philo_id;
	int		philo_died;
	t_philo	*philos;
	t_philo spy_thread;
}				t_s;


int		ft_atoi(const char *str);
void	*ft_calloc(int size, int len);
int		parcer(t_s *s);
int		create_forks(t_s *s);
void	spy_func(t_s *s);
int		ft_exit(char *str);
void	life(void *s);
void	spy_func(t_s *s);
int	create_phtreads(t_s *s);
#endif
