/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourdon <abourdon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 18:36:53 by abourdon          #+#    #+#             */
/*   Updated: 2023/04/15 12:11:34 by abourdon         ###   ########.fr       */
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

int	main(int ac, char **av)
{
	t_arg	arg;

	if (ft_check_arg(ac, av) == 1)
		return (1);
	if (ft_init_args(ac, av, &arg) == 1)
		return (1);
	if (ft_init_mutex(&arg) == 1)
		return (1);
	printf("%d\n", arg.nbr_philo);
	printf("%d\n", arg.time_to_die);
	printf("%d\n", arg.time_to_eat);
	printf("%d\n", arg.time_to_sleep);
	printf("%d\n", arg.nb_time_must_eat);
	free_all(&arg);
	return (0);
}
