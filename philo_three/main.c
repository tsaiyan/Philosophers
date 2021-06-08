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
#include <stdio.h>

int	main(int argc, char **argv)
{
	t_s	*s;

	s = ft_calloc(sizeof(t_s), 1);
	s->a_r_g_c = argc;
	s->argv = argv;
	parcer(s);
	init_sem(s);
	create_processes(s);
	my_usleep(s->time_2_die);
	errno = 0;
	sem_wait(s->stop);
	if (errno)
	{
		perror("////////////////////////////////////1");
		s = NULL;
	}
	kill_pid(s);
	return (0);
}
