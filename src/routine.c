/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourdon <abourdon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 11:35:44 by abourdon          #+#    #+#             */
/*   Updated: 2023/04/26 17:12:35 by abourdon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ft_check_nbr_meals(t_philo *philo)
{
	if (philo->total_nbr_of_must_eat == -1)
		return (0);
	if (philo->actual_meals == philo->total_nbr_of_must_eat)
		return (1);
	return (0);
}

// void	ft_check_die(t_philo *philo, int i)
// {
// 	philo->arg->stop = 1;
// 	pthread_mutex_lock(&philo->arg->print_lock);
// 	printf("\033[0;37m%ld %d is died\n\033[0;37m", ft_get_time() - philo[i].start_time, philo[i].philo_id);
// 	pthread_mutex_unlock(&philo->arg->print_lock);
// }

// void	*thread_routine_die(void *arg)
// {
// 	int	i;
// 	t_philo	*philo;

// 	i = 0;
// 	philo = (t_philo *)arg;
// 	while (i < philo->nbr_philo)
// 	{
// 		if (ft_get_time() - philo[i].start_time > philo[i].time_to_die || ft_get_time() - philo[i].time_of_last_must_eat > philo[i].time_to_die)
// 			ft_check_die(philo, i);
// 		i++;
// 	}
// 	return (NULL);
// }

// int	ft_check_die(t_philo *philo)
// {
// 	pthread_mutex_lock(&philo->arg->check_died);
// 	if (ft_get_time() - philo->start_time > philo->time_to_die || ft_get_time() - philo->time_of_last_must_eat > philo->time_to_die)
// 	{
// 		if (philo->arg->stop == 0)
// 		{
// 			philo->arg->stop = 1;
// 			pthread_mutex_lock(&philo->arg->print_lock);
// 			printf("\033[0;37m%ld %d is died\n\033[0;37m", ft_get_time() - philo->start_time, philo->philo_id);
// 			pthread_mutex_unlock(&philo->arg->print_lock);
// 		}
// 		pthread_mutex_unlock(&philo->arg->check_died);
// 		return (1);
// 	}
// 	pthread_mutex_unlock(&philo->arg->check_died);
// 	return (0);
// }


void	*thread_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	philo->time_of_last_must_eat = ft_get_time();
	philo->start_time = ft_get_time();
	while (philo->arg->stop == 0)
	{
		if (philo->arg->stop == 1 || ft_check_nbr_meals(philo) == 1)
			return (NULL);
		// printf("philo ID: %d ==> fork\n", philo->philo_id);
		take_fork(philo);
		if (philo->arg->stop == 1 || ft_check_nbr_meals(philo) == 1)
			return (NULL);
		// printf("philo ID: %d ==> eat\n", philo->philo_id);
		eating(philo);
		if (philo->arg->stop == 1 || ft_check_nbr_meals(philo) == 1)
			return (NULL);
		// printf("philo ID: %d ==> sleep\n", philo->philo_id);
		sleeping(philo);
		if (philo->arg->stop == 1 || ft_check_nbr_meals(philo) == 1)
			return (NULL);
		// printf("philo ID: %d ==> think\n", philo->philo_id);
		thinking(philo);
		if (philo->arg->stop == 1 || ft_check_nbr_meals(philo) == 1)
			return (NULL);
	}
	return (NULL);
}
