/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourdon <abourdon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 11:52:48 by abourdon          #+#    #+#             */
/*   Updated: 2023/04/15 12:32:00 by abourdon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ft_init_args(int ac, char **av, t_arg *arg)
{
	arg->nbr_philo = ft_atoi(av[1]);
	if (arg->nbr_philo < 1)
	{
		printf("Incorrect number of philosopher\n");
		return (1);
	}
	arg->time_to_die = ft_atoi(av[2]);
	arg->time_to_eat = ft_atoi(av[3]);
	arg->time_to_sleep = ft_atoi(av[4]);
	if (ac == 5)
		arg->nb_time_must_eat = -1;
	else if (ac == 6)
	{
		arg->nb_time_must_eat = ft_atoi(av[5]);
		if (arg->nb_time_must_eat < 1)
		{
			printf("Incorrect number of times each philosopher must_eat\n");
			return (1);
		}
	}
	return (0);
}

int	ft_init_mutex(t_arg *arg)
{
	int	nb;
	pthread_mutex_t	*mutex;

	nb = arg->nbr_philo;
	mutex = malloc(sizeof(pthread_mutex_t) * arg->nb_philo);
	if (!mutex)
		return (1);
	while (nb != 0)
	{
		if (pthread_mutex_init(&mutex[nb], NULL) != 0)
		{
			//protection
			return (1);
		}
		nb--;
	}
	if (pthread_mutex_init(&arg->lock, NULL) != 0);
	{
		//protection
		return (1);
	}
	arg->forks = mutex;
	return (0);
}