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
#include <sys/time.h>

typedef struct	s_philo
{
	pthread_t	thread;
	int			id;
	int			left_hand;
	int			right_hand;
	
	long		time_zero;
	long		time_last_eat;
	int			eating;
	int			eat_count;
	int			finish_eat;
}				t_philo;

typedef struct		s_s
{
	pthread_mutex_t	output;
	pthread_mutex_t	mutex;
	pthread_mutex_t	*forks;
	int				argс;
	char			**argv;
	
	long			time_4_eat;
	long			time_4_sleep;
	long			time_2_die;
	int				min_2_eat;
	int				philo_count;
	
	int				philo_id;
	int				philo_died;
	t_philo			*philos;
	t_philo			spy_thread;
	long			start_time;
	int				exit;
}					t_s;


int		ft_atoi(const char *str);
void	*ft_calloc(int size, int len);
int		parcer(t_s *s);
int		create_forks(t_s *s);
void	spy_func(t_s *s);
int		ft_exit(char *str);
void	life(void *s);
void	spy_func(t_s *s);
int		create_pthreads(t_s *s);
long	get_time(void);
void	my_usleep(long wait);
int		ft_strlen(char *str);
void	mutexed_print(t_s *s, char *str, int id);
void	life(void *all);
void	spy_func(t_s *s);
void	mutex_destroy(t_s *s);
#endif
