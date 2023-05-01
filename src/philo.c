/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourdon <abourdon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 18:36:53 by abourdon          #+#    #+#             */
/*   Updated: 2023/05/01 19:04:36 by abourdon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	printphilo(t_arg *arg)
{
	int	i;

	i = 0;
	while (i < arg->nbr_philo)
	{
		printf("philo ID: %d\n", arg->philo_tabstruct[i].philo_id);
		printf("philo nb: %d\n", arg->philo_tabstruct[i].nbr_philo);
		printf("total nbr of must eat: %d\n", arg->philo_tabstruct[i].total_nbr_of_must_eat);
		printf("time to eat: %d\n", arg->philo_tabstruct[i].time_to_eat);
		printf("time to sleep: %d\n", arg->philo_tabstruct[i].time_to_sleep);
		printf("time to die: %d\n", arg->philo_tabstruct[i].time_to_die);
		printf("time of last must eat: %ld\n", arg->philo_tabstruct[i].time_of_last_must_eat);
		printf("---------------------------------------------\n");
		i++;
	}
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
	if (ft_init_philo(&arg) == 1)
		return (1);
	// printphilo(&arg);
	if (ft_init_thread(&arg) == 1)
		return (1);
	unlock_and_destroy_mutex(&arg);
	free_all(&arg);
	return (0);
}
