//
//  utils_logic.c
//  philosopher
//
//  Created by Torres Saiyan on 6/7/21.
//  Copyright © 2021 Torres Saiyan. All rights reserved.
//

#include "header.h"


void	mutex_destroy(t_s *s)
{
	int i;

	i = -1;
	pthread_mutex_destroy(&s->output);
	while (++i < s->philo_count)
		pthread_mutex_destroy(&s->forks[i]);
}


void	my_usleep(long wait)
{
	long time;

	time = get_time();
	while (get_time() - time < wait)
		usleep(100);

	
}
long	get_time(void)
{
	struct timeval time;

	gettimeofday(&time, NULL);
	return ((long)time.tv_sec * 1000 + (long)time.tv_usec / 1000);
}
