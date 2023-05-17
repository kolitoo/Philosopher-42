/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourdon <abourdon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 17:28:19 by abourdon          #+#    #+#             */
/*   Updated: 2023/05/17 19:44:11 by abourdon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	end_of_threads(t_arg *arg, int j, pthread_t	*threads)
{
	if (check_loop(arg->philo_tabstruct) != 0)
	{
		while (++j < arg->nbr_philo)
			pthread_join(threads[j], NULL);
		if (arg->flag == 1)
			printf("each philo ate %d times\n", arg->nb_time_must_eat);
	}
	arg->threads = threads;
}

int	ft_init_thread(t_arg *arg, int i, int j, int k)
{
	pthread_t	*threads;

	threads = malloc(sizeof(pthread_t) * arg->nbr_philo);
	if (!threads)
	{
		free_all(arg, 1);
		destroy_mutex(arg, 3);
		return (1);
	}
	while (++i < arg->nbr_philo)
	{
		arg->philo_tabstruct[i].time_of_last_must_eat = ft_get_time();
		if (pthread_create(&threads[i], NULL, thread_routine,
				(void *)&arg->philo_tabstruct[i]) != 0)
		{
			arg->threads = threads;
			while (k < i)
				pthread_detach(threads[i]);
			free_and_destroy(arg);
			return (1);
		}
	}
	end_of_threads(arg, j, threads);
	return (0);
}

static int	init_others_mutex(t_arg *arg)
{
	if (pthread_mutex_init(&arg->print_lock, NULL) != 0)
	{
		destroy_mutex(arg, 1);
		return (1);
	}
	if (pthread_mutex_init(&arg->last_time_eat, NULL) != 0)
	{
		destroy_mutex(arg, 2);
		return (1);
	}
	if (pthread_mutex_init(&arg->check_dead, NULL) != 0)
	{
		destroy_mutex(arg, 3);
		return (1);
	}
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
			free (mutex);
			return (1);
		}
	}
	arg->mutex_tab = mutex;
	if (init_others_mutex(arg) == 1)
		return (1);
	return (0);
}
