/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourdon <abourdon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 11:35:44 by abourdon          #+#    #+#             */
/*   Updated: 2023/05/01 19:03:14 by abourdon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*is_dead(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	ft_usleep(philo->arg->time_to_die + 1);
	return (NULL);
}

void	*thread_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->philo_id % 2 != 0)
		ft_usleep(philo->arg->time_to_eat / 10);
	philo->time_of_last_must_eat = ft_get_time();
	while (philo->stop == 0)
	{
		// pthread_create(&philo->thread_death_id, NULL, is_dead, arg);
		take_fork(philo);
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}
