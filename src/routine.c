/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourdon <abourdon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 11:35:44 by abourdon          #+#    #+#             */
/*   Updated: 2023/05/02 23:05:16 by abourdon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*is_dead(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	ft_usleep(philo->time_to_die + 1);
	pthread_mutex_lock(&philo->arg->check_died);
	if (philo->arg->dead == 1)
		return (NULL);
	pthread_mutex_lock(&philo->arg->last_time_eat);
	if (ft_get_time() - philo->time_of_last_must_eat >= philo->time_to_die)
	{
		pthread_mutex_lock(&philo->arg->print_lock);
		print_action(philo, "died", 0);
		pthread_mutex_unlock(&philo->arg->print_lock);
		philo->arg->dead = 1;
	}
	pthread_mutex_unlock(&philo->arg->check_died);
	pthread_mutex_unlock(&philo->arg->last_time_eat);
	return (NULL);
}

void	*thread_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->philo_id % 2 != 0)
		ft_usleep(philo->arg->time_to_eat / 10);
	philo->time_of_last_must_eat = ft_get_time();
	while (philo->stop == 0 && philo->arg->dead == 0)
	{
		pthread_create(&philo->thread_death_id, NULL, is_dead, philo);
		if (philo->arg->dead != 0)
			return (NULL);
		take_fork(philo);
		if (philo->arg->dead != 0)
			return (NULL);
		eating(philo);
		if (philo->arg->dead != 0)
			return (NULL);
		sleeping(philo);
		if (philo->arg->dead != 0)
			return (NULL);
		thinking(philo);
		if (philo->arg->dead != 0)
			return (NULL);
		pthread_detach(philo->thread_death_id);
	}
	return (NULL);
}
