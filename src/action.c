/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourdon <abourdon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 12:41:33 by abourdon          #+#    #+#             */
/*   Updated: 2023/05/12 17:07:28 by abourdon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	take_fork(t_philo *philo)
{
	if (philo->nbr_philo == 1)
		pthread_mutex_lock(philo->left_fork);
	else
	{
		if (philo->philo_id % 2 != 0)
		{
			pthread_mutex_lock(philo->left_fork);
			pthread_mutex_lock(philo->right_fork);
		}
		else
		{
			pthread_mutex_lock(philo->right_fork);
			pthread_mutex_lock(philo->left_fork);
		}
	}
	pthread_mutex_lock(&philo->arg->print_lock);
	print_action(philo, "has taken a fork", 1);
	if (philo->nbr_philo == 1)
	{
		ft_usleep(philo->time_to_die);
		print_action(philo, "died", 0);
		check_death(philo, 1);
		pthread_mutex_unlock(&philo->arg->print_lock);
		pthread_mutex_unlock(philo->left_fork);
		return ;
	}
	print_action(philo, "has taken a fork", 1);
	pthread_mutex_unlock(&philo->arg->print_lock);
	if (check_death(philo, 0) != 0)
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
	}
}

void	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->arg->print_lock);
	print_action(philo, "is eating", 2);
	pthread_mutex_unlock(&philo->arg->print_lock);
	pthread_mutex_lock(&philo->arg->last_time_eat);
	philo->actual_meals++;
	philo->time_of_last_must_eat = ft_get_time();
	pthread_mutex_unlock(&philo->arg->last_time_eat);
	// if (philo->actual_meals == philo->total_nbr_of_must_eat)
	// {
	// 	if (philo->philo_id + 1 == philo->nbr_philo)
	// 		philo->arg->stop = 1;
	// 	philo->stop = 1;
	// }
	// pthread_mutex_lock(&philo->arg->last_time_eat);
	// philo->time_of_last_must_eat = ft_get_time();
	// pthread_mutex_unlock(&philo->arg->last_time_eat);
	ft_usleep(philo->arg->time_to_eat);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void	sleeping(t_philo *philo)
{
	pthread_mutex_lock(&philo->arg->print_lock);
	print_action(philo, "is sleeping", 3);
	pthread_mutex_unlock(&philo->arg->print_lock);
	ft_usleep(philo->arg->time_to_sleep);
}

void	thinking(t_philo *philo)
{
	pthread_mutex_lock(&philo->arg->print_lock);
	print_action(philo, "is thinking", 4);
	pthread_mutex_unlock(&philo->arg->print_lock);
}
