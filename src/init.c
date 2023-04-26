/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourdon <abourdon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 11:52:48 by abourdon          #+#    #+#             */
/*   Updated: 2023/04/26 17:14:39 by abourdon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ft_init_args(int ac, char **av, t_arg *arg)
{
	arg->nbr_philo = ft_atoi(av[1]);
	arg->time_to_die = ft_atoi(av[2]);
	arg->time_to_eat = ft_atoi(av[3]);
	arg->time_to_sleep = ft_atoi(av[4]);
	if (ft_check_values(ac, arg, av) == 1)
		return (1);
	arg->stop = 0;
	arg->mutex_lock = 0;
	return (0);
}

int	ft_init_philo(t_arg *arg)
{
	t_philo	*philo;
	int		i;

	i = 0;
	philo = malloc(sizeof(t_philo) * arg->nbr_philo);
	if (!philo)
	{
		//protect
		return (1);
	}
	while (i != arg->nbr_philo)
	{
		philo[i].philo_id = i + 1;
		philo[i].nbr_philo = arg->nbr_philo;
		philo[i].total_nbr_of_must_eat = arg->nb_time_must_eat;
		// printf("Philo ID: %d\ntotal_nbr_of_must_eat: %d\n", philo[i].philo_id, philo[i].total_nbr_of_must_eat);
		philo[i].actual_meals = 0;
		philo[i].time_to_eat = arg->time_to_eat;
		philo[i].time_to_die = arg->time_to_die;
		philo[i].die = 0;
		philo[i].time_to_sleep = arg->time_to_sleep;
		philo[i].time_of_last_must_eat = ft_get_time();
		philo[i].left_fork = &arg->mutex_tab[philo[i].philo_id];
		philo[i].right_fork = &arg->mutex_tab[philo[i].philo_id + 1 % arg->nbr_philo];
		philo[i].arg = arg;
		i++;
	}
	arg->philo_tabstruct = philo;
	return (0);
}

int	ft_init_thread(t_arg *arg)
{
	int	i;
	int	j;
	pthread_t	*threads;
	// pthread_t	thread_die;

	i = arg->nbr_philo;
	j = i;
	threads = malloc(sizeof(pthread_t) * i);//protect
	if (!threads)
	{
		//protect
		return (1);
	}
	while (i--)
	{
		pthread_create(&threads[i], NULL, thread_routine, (void *)&arg->philo_tabstruct[i]);
	}
	// pthread_create(&thread_die, NULL, thread_routine_die, (void *)arg->philo_tabstruct);
	// pthread_join(thread_die, NULL);
	while (j--)
	{
		pthread_join(threads[j], NULL);
	}
	arg->threads = threads;
	return (0);
}

int	ft_init_mutex(t_arg *arg)
{
	int				i;
	pthread_mutex_t	*mutex;

	i = arg->nbr_philo;
	mutex = malloc(sizeof(pthread_mutex_t) * i);
	if (!mutex)
	{
		//protect
		return (1);
	}
	while (i--)
	{
		pthread_mutex_init(&mutex[i], NULL);//protect
	}
	pthread_mutex_init(&arg->print_lock, NULL);//protect
	// pthread_mutex_init(&arg->check_died, NULL);
	arg->mutex_tab = mutex;
	return (0);
}
