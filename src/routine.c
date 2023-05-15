/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourdon <abourdon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 11:35:44 by abourdon          #+#    #+#             */
/*   Updated: 2023/05/15 22:12:59 by abourdon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	check_death(t_philo *philo, int i)
{
	// pthread_mutex_lock(&philo->arg->check_dead);
	if (i != 0)
		philo->arg->dead = i;
	if (philo->arg->dead != 0)
	{
		// pthread_mutex_unlock(&philo->arg->check_dead);
		return (1);
	}
	// pthread_mutex_unlock(&philo->arg->check_dead);
	return (0);
}

int	count_meals(t_philo *philo)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	// pthread_mutex_lock(&philo->arg->last_time_eat);
	while (++i < philo->nbr_philo)
	{
		if (philo[i].actual_meals == philo->total_nbr_of_must_eat)
			count++;
	}
	if (count == philo->nbr_philo)
	{
		printf("each philosophers ate %d times\n", philo->total_nbr_of_must_eat);
		// pthread_mutex_unlock(&philo->arg->last_time_eat);
		return (1);
	}
	// pthread_mutex_unlock(&philo->arg->last_time_eat);
	return (0);
}

int	check(t_philo *philo)
{
	long	time_now;
	int		i;

	i = 0;
	while (1)
	{
		i = -1;
		while (++i < philo->nbr_philo)
		{
			time_now = ft_get_time();
			// pthread_mutex_lock(&philo->arg->last_time_eat);
			if (time_now - philo[i].time_of_last_must_eat > philo[i].time_to_die)
			{
				// pthread_mutex_unlock(&philo->arg->last_time_eat);
				pthread_mutex_lock(&philo->arg->print_lock);
				print_action(&philo[i], "died", 5);
				pthread_mutex_unlock(&philo->arg->print_lock);
				check_death(&philo[i], 1);
				return (1);
			}
			// pthread_mutex_unlock(&philo->arg->last_time_eat);
			if (count_meals(philo) == 1)
			{
				check_death(&philo[i], 2);
				return (1);
			}
		}
	}
	return (0);
}

void	*thread_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	// if (philo->philo_id % 2 != 0)
	// 	ft_usleep(philo->arg->time_to_eat / 2);
	// philo->time_of_last_must_eat = ft_get_time();
	while (check_death(philo, 0) == 0)
	{
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
	}
	return (NULL);
}
