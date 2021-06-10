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

// wait sem while all didn't ate

void	*check_all_ate(void *void_philo)
{
	t_s		*s;
	t_philo	*philo;
	int		i;

	i = 0;
	philo = (t_philo *)void_philo;
	s = (t_s *)philo->all;
	while (++i <= s->philo_count)
		sem_wait(s->sem_eat_count);
	sem_post(s->stop);
	return (NULL);
}
