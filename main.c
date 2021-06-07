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


int main(int argc, char **argv)
{
	
	t_s *s;
	s = ft_calloc(sizeof(t_s), 1);
	s->argс = argc;
	s->argv = argv;
	parcer(s);
	pthread_mutex_init(&s->output, NULL);
	create_forks(s);
	create_pthreads(s);
	while(!s->exit)
		usleep(500000);
	return 0;
}
