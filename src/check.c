/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourdon <abourdon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 11:14:28 by abourdon          #+#    #+#             */
/*   Updated: 2023/05/01 19:12:24 by abourdon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ft_check_arg(int ac, char **av)
{
	int	i;

	i = 1;
	if (ac == 5 || ac == 6)
	{
		while (av[i] != NULL)
		{
			if (ft_is_digit(av[i]) == 1)
			{
				printf("Invalid arguments\n");
				return (1);
			}
			i++;
		}
	}
	else
	{
		printf("Invalid number of arguments, write: \n[number_of_philosophers] \
		[time_to_die] [time_to_eat] [time_to_sleep]\
		[number_of_times_each_philosopher_must_eat]\n");
		return (1);
	}
	return (0);
}

static int	ft_check_values2(t_arg *arg)
{
	if (arg->nbr_philo <= 0)
	{
		printf("Wrong number of philo\n");
		return (1);
	}
	if (arg->time_to_die <= 0)
	{
		printf("Wrong time to die\n");
		return (1);
	}
	if (arg->time_to_eat <= 0)
	{
		printf("Wrong time to eat\n");
		return (1);
	}
	if (arg->time_to_sleep <= 0)
	{
		printf("Wrong time to sleep\n");
		return (1);
	}
	return (0);
}

int	ft_check_values(int ac, t_arg *arg, char **av)
{
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
	if (ft_check_values2(arg) == 1)
		return (1);
	return (0);
}
