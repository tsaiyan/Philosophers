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

int	main(int argc, char **argv)
{
	t_s	*s;

	s = ft_calloc(sizeof(t_s), 1);
	s->a_r_g_c = argc;
	s->argv = argv;
	parcer(s);
	if (pthread_mutex_init(&s->output, NULL) != 0)
		ft_exit("mutex output init error");
	create_forks(s);
	create_pthreads(s);
	if (pthread_join(s->philos[0].thread, NULL))
		return (0);
}
