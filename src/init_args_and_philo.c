/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_args_and_philo.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourdon <abourdon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 11:52:48 by abourdon          #+#    #+#             */
/*   Updated: 2023/05/17 17:32:09 by abourdon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ft_init_args(int ac, char **av, t_arg *arg)
{
	arg->nbr_philo = ft_atoi(av[1], 0);
	arg->time_to_die = ft_atoi(av[2], 0);
	arg->time_to_eat = ft_atoi(av[3], 0);
	arg->time_to_sleep = ft_atoi(av[4], 0);
	if (ft_check_values(ac, arg, av) == 1)
		return (1);
	arg->dead = 0;
	arg->count_meals = 0;
	arg->flag = 0;
	return (0);
}

static void	init_tab(t_arg *arg, t_philo *philo, int i)
{
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
		philo[i].time_to_sleep = arg->time_to_sleep;
		philo[i].left_fork = &arg->mutex_tab[philo[i].philo_id];
		if (arg->nbr_philo != 1)
			philo[i].right_fork = &arg->mutex_tab[(philo[i].philo_id + 1)
				% arg->nbr_philo];
		philo[i].arg = arg;
		i++;
	}
	arg->philo_tabstruct = philo;
}

int	ft_init_philo(t_arg *arg)
{
	t_philo	*philo;
	int		i;

	i = 0;
	philo = NULL;
	philo = malloc(sizeof(t_philo) * arg->nbr_philo);
	if (!philo)
	{
		free(arg->mutex_tab);
		destroy_mutex(arg, 4);
		return (1);
	}
	init_tab(arg, philo, i);
	return (0);
}
