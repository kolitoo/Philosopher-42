/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourdon <abourdon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 11:35:44 by abourdon          #+#    #+#             */
/*   Updated: 2023/05/12 17:07:03 by abourdon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	check_death(t_philo *philo, int i)
{
	pthread_mutex_lock(&philo->arg->check_dead);
	if (i != 0)
		philo->arg->dead = i;
	if (philo->arg->dead != 0)
	{
		pthread_mutex_unlock(&philo->arg->check_dead);
		return (1);
	}
	pthread_mutex_unlock(&philo->arg->check_dead);
	return (0);
}

void	*is_dead(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	ft_usleep(philo->time_to_die + 2);
	pthread_mutex_lock(&philo->arg->check_died);
	pthread_mutex_lock(&philo->arg->last_time_eat);
	if (check_death(philo, 0) != 0)
	{
		// pthread_mutex_unlock(&philo->arg->check_died);
		pthread_mutex_unlock(&philo->arg->last_time_eat);
		return (NULL);
	}
	if (ft_get_time() - philo->time_of_last_must_eat >= philo->time_to_die)
	{
		pthread_mutex_unlock(&philo->arg->check_died);
		// pthread_mutex_unlock(&philo->arg->last_time_eat);
		pthread_mutex_lock(&philo->arg->print_lock);
		print_action(philo, "died", 0);
		pthread_mutex_unlock(&philo->arg->print_lock);
		check_death(philo, 1);
	}
	// pthread_mutex_unlock(&philo->arg->check_died);
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
	while (philo->stop == 0 && check_death(philo, 0) == 0)
	{
		pthread_create(&philo->thread_death_id, NULL, is_dead, philo);
		if (check_death(philo, 0) != 0)
			return (NULL);
		take_fork(philo);
		if (check_death(philo, 0) != 0)
			return (NULL);
		eating(philo);
		if (check_death(philo, 0) != 0)
			return (NULL);
		sleeping(philo);
		if (check_death(philo, 0) != 0)
			return (NULL);
		thinking(philo);
		if (check_death(philo, 0) != 0)
			return (NULL);
		if (philo->actual_meals == philo->total_nbr_of_must_eat)
		{
			if (philo->philo_id + 1 == philo->nbr_philo)
				philo->arg->stop = 1;
			philo->stop = 1;
		}
		// pthread_join(philo->thread_death_id, NULL);
		pthread_detach(philo->thread_death_id);
	}
	return (NULL);
}
