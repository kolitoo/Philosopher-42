/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourdon <abourdon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 11:52:48 by abourdon          #+#    #+#             */
/*   Updated: 2023/05/15 20:19:15 by abourdon         ###   ########.fr       */
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
	arg->dead = 0;
	arg->mutex_lock = 0;
	arg->stop = 0;
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
		free(arg->mutex_tab);
		unlock_and_destroy_mutex(arg, 3);
		return (1);
	}
	while (i != arg->nbr_philo)
	{
		philo[i].philo_id = i;
		philo[i].nbr_philo = arg->nbr_philo;
		philo[i].stop = 0;
		philo[i].start_time = ft_get_time();
		philo[i].total_nbr_of_must_eat = arg->nb_time_must_eat;
		philo[i].actual_meals = 0;
		philo[i].time_to_eat = arg->time_to_eat;
		philo[i].time_to_die = arg->time_to_die;
		philo[i].die = 0;
		philo[i].time_to_sleep = arg->time_to_sleep;
		philo[i].time_of_last_must_eat = ft_get_time();
		philo[i].left_fork = &arg->mutex_tab[philo[i].philo_id];
		if (arg->nbr_philo != 1)
			philo[i].right_fork = &arg->mutex_tab[(philo[i].philo_id + 1) % arg->nbr_philo];
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
	pthread_t		*threads;

	i = -1;
	j = -1;
	threads = malloc(sizeof(pthread_t) * arg->nbr_philo);
	if (!threads)
	{
		free(arg->mutex_tab);
		free(arg->philo_tabstruct);
		unlock_and_destroy_mutex(arg, 3);
		return (1);
	}
	while (++i < arg->nbr_philo)
	{
		if (pthread_create(&threads[i], NULL, thread_routine, (void *)&arg->philo_tabstruct[i]) != 0)
		{
			arg->threads = threads;
			return (1);
		}
	}
	if (check(arg->philo_tabstruct) != 0)
	{
		while (++j < arg->nbr_philo)
		{
			if (pthread_join(threads[j], NULL) != 0)
			{
				arg->threads = threads;
				return (1);
			}
		}
	}
	arg->threads = threads;
	return (0);
}

int	ft_init_mutex(t_arg *arg)
{
	int				i;
	int				j;
	int				k;
	pthread_mutex_t	*mutex;

	i = -1;
	j = -1;
	k = arg->nbr_philo;
	mutex = malloc(sizeof(pthread_mutex_t) * k);
	if (!mutex)
		return (1);
	while (++i < k)
	{
		if (pthread_mutex_init(&mutex[i], NULL) != 0)
		{
			while (++j < i)
				pthread_mutex_destroy(&mutex[j]);
			return (1);
		}
	}		
	arg->mutex_tab = mutex;
	if (pthread_mutex_init(&arg->print_lock, NULL) != 0)
	{
		unlock_and_destroy_mutex(arg, 1); 
		return (1);
	}
	if (pthread_mutex_init(&arg->last_time_eat, NULL) != 0)
	{
		unlock_and_destroy_mutex(arg, 3); //modifier
		return (1);
	}
	if (pthread_mutex_init(&arg->check_dead, NULL) != 0)
	{
		unlock_and_destroy_mutex(arg, 4);
		return (1);
	}
	return (0);
}
