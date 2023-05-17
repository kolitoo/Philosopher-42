/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourdon <abourdon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 11:35:44 by abourdon          #+#    #+#             */
/*   Updated: 2023/05/17 19:38:23 by abourdon         ###   ########.fr       */
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
		return (philo->arg->dead);
	}
	pthread_mutex_unlock(&philo->arg->check_dead);
	return (0);
}

static int	if_die(int *i, long time_now, t_philo *philo)
{
	time_now = ft_get_time();
	pthread_mutex_lock(&philo->arg->last_time_eat);
	if (time_now - philo[*i].time_of_last_must_eat
		> philo[*i].time_to_die)
	{
		pthread_mutex_unlock(&philo->arg->last_time_eat);
		pthread_mutex_lock(&philo->arg->print_lock);
		print_action(&philo[*i], "died", 5);
		pthread_mutex_unlock(&philo->arg->print_lock);
		check_death(&philo[*i], 1);
		return (1);
	}
	pthread_mutex_unlock(&philo->arg->last_time_eat);
	return (0);
}

int	check_loop(t_philo *philo)
{
	long	time_now;
	int		i;

	i = 0;
	time_now = 0;
	while (1)
	{
		i = -1;
		while (++i < philo->nbr_philo)
		{
			if (if_die(&i, time_now, philo) == 1)
				return (1);
			if (check_meals(&philo[i]) == 2)
			{
				philo->arg->flag = 1;
				return (2);
			}
		}
	}
	return (0);
}

int	check_meals(t_philo *philo)
{
	pthread_mutex_lock(&philo->arg->last_time_eat);
	if (philo->stop == 1)
	{
		if (philo->arg->count_meals == philo->nbr_philo)
		{
			check_death(philo, 2);
			pthread_mutex_unlock(&philo->arg->last_time_eat);
			return (2);
		}
		pthread_mutex_unlock(&philo->arg->last_time_eat);
		return (1);
	}
	pthread_mutex_unlock(&philo->arg->last_time_eat);
	return (0);
}

void	*thread_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->philo_id % 2 != 0)
		ft_usleep(philo->arg->time_to_eat / 2);
	while (check_death(philo, 0) == 0)
	{
		if (check_death(philo, 0) != 0)
			return (NULL);
		take_fork(philo);
		if (check_death(philo, 0) != 0)
			return (NULL);
		eating(philo);
		if (check_meals(philo) != 0 || check_death(philo, 0) != 0)
			return (NULL);
		sleeping(philo);
		if (check_death(philo, 0) != 0)
			return (NULL);
		thinking(philo);
	}
	return (NULL);
}
