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
# define HEADER_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <errno.h>
# include <sys/time.h>
# include <semaphore.h>

typedef struct s_philo
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
	void		*all;
}				t_philo;

typedef struct s_s
{
	sem_t			*output;
	sem_t			*forks;
	int				a_r_g_c;
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
int		init_sem(t_s *s);
int		ft_exit(char *str);
void	*life(void *void_philos);
void	*spy_func(void *all);
int		create_pthreads(t_s *s);
long	get_time(void);
void	my_usleep(long wait);
int		ft_strlen(char *str);
void	semaphored_print(t_s *s, char *str, int id);
void	my_sem_destroy(t_s *s);
#endif
