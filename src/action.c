/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourdon <abourdon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 12:41:33 by abourdon          #+#    #+#             */
/*   Updated: 2023/05/01 19:05:06 by abourdon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	take_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(&philo->arg->print_lock);
	printf("\033[0;31m%ld %d has taken a fork\n\033[0;37m", ft_get_time() - philo->start_time, philo->philo_id + 1);
	printf("\033[0;31m%ld %d has taken a fork\n\033[0;37m", ft_get_time() - philo->start_time, philo->philo_id + 1);
	philo->arg->mutex_lock = 1;
	pthread_mutex_unlock(&philo->arg->print_lock);
}

void	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->arg->print_lock);
	printf("\033[0;33m%ld %d is eating\n\033[0;37m", ft_get_time() - philo->start_time, philo->philo_id + 1);
	pthread_mutex_unlock(&philo->arg->print_lock);
	philo->actual_meals++;
	if (philo->actual_meals == philo->total_nbr_of_must_eat)
	{
		if (philo->philo_id + 1 == philo->nbr_philo)
			philo->arg->stop = 1;
		philo->stop = 1;
	}
	philo->time_of_last_must_eat = ft_get_time();
	ft_usleep(philo->arg->time_to_eat);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void	sleeping(t_philo *philo)
{
	pthread_mutex_lock(&philo->arg->print_lock);
	printf("\033[0;35m%ld %d is sleeping\n\033[0;35m", ft_get_time() - philo->start_time, philo->philo_id + 1);
	pthread_mutex_unlock(&philo->arg->print_lock);
	ft_usleep(philo->arg->time_to_sleep);
}

void	thinking(t_philo *philo)
{
	pthread_mutex_lock(&philo->arg->print_lock);
	printf("\033[0;34m%ld %d is thinking\n\033[0;37m", ft_get_time() - philo->start_time, philo->philo_id + 1);
	pthread_mutex_unlock(&philo->arg->print_lock);
}
