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
# include <signal.h>

typedef struct s_philo
{
	pthread_t	thread;
	int			id;

	long		time_zero;
	long		time_last_eat;
	int			eat_count;
	void		*all;
}				t_philo;

typedef struct s_s
{
	sem_t			*output;
	sem_t			*forks;
	sem_t			*stop;
	sem_t			*sem_eat_count;
	int				a_r_g_c;
	char			**argv;

	long			time_4_eat;
	long			time_4_sleep;
	long			time_2_die;
	int				min_2_eat;
	int				philo_count;

	int				philo_id;
	int				philo_died;
	t_philo			**philos;
	pthread_t		finish_eat;
	long			start_time;
	int				exit;
	int				pid_array[200];
}					t_s;

int		ft_atoi(const char *str);
void	*ft_calloc(int size, int len);
int		parcer(t_s *s);
int		init_sem(t_s *s);
int		ft_exit(char *str);
void	life(t_philo *philo);
void	*wait_eat_finish(void *all);
int		create_processes(t_s *s);
long	get_time(void);
void	my_usleep(long wait);
int		ft_strlen(char *str);
void	semaphored_print(t_s *s, char *str, int id);
void	my_sem_destroy(t_s *s);
void	*hara_kiri(void *void_philo);
void	kill_pid(t_s *s);
void	*check_all_ate(void *void_philo);
int		ft_isdigit(int c);
#endif
