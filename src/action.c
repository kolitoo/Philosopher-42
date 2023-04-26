/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourdon <abourdon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 12:41:33 by abourdon          #+#    #+#             */
/*   Updated: 2023/04/26 16:52:10 by abourdon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	take_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(&philo->arg->print_lock);
	printf("\033[0;31m%ld %d has taken a fork\n\033[0;37m", ft_get_time() - philo->start_time, philo->philo_id);
	printf("\033[0;31m%ld %d has taken a fork\n\033[0;37m", ft_get_time() - philo->start_time, philo->philo_id);
	philo->arg->mutex_lock = 1;
	pthread_mutex_unlock(&philo->arg->print_lock);
}

void	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->arg->print_lock);
	printf("\033[0;33m%ld %d is eating\n\033[0;37m", ft_get_time() - philo->start_time, philo->philo_id);
	philo->arg->mutex_lock = 0;
	pthread_mutex_unlock(&philo->arg->print_lock);
	philo->actual_meals++;
	philo->time_of_last_must_eat = ft_get_time();
	ft_usleep(philo->time_to_eat);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}
 
void	sleeping(t_philo *philo)
{
	pthread_mutex_lock(&philo->arg->print_lock);
	printf("\033[0;37m%ld %d is sleeping\n\033[0;37m", ft_get_time() - philo->start_time, philo->philo_id);
	ft_usleep(philo->time_to_sleep);
	pthread_mutex_unlock(&philo->arg->print_lock);
}

void	thinking(t_philo *philo)
{
	pthread_mutex_lock(&philo->arg->print_lock);
	printf("\033[0;34m%ld %d is thinking\n\033[0;37m", ft_get_time() - philo->start_time, philo->philo_id);
	pthread_mutex_unlock(&philo->arg->print_lock);
}