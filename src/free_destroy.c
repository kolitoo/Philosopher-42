/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_destroy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourdon <abourdon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 12:09:54 by abourdon          #+#    #+#             */
/*   Updated: 2023/05/17 17:17:11 by abourdon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	free_and_destroy(t_arg *arg)
{
	destroy_mutex(arg, 4);
	free_all(arg, 2);
}

void	free_all(t_arg *arg, int i)
{
	if (i == 1)
	{
		free(arg->threads);
		free(arg->mutex_tab);
		return ;
	}
	else
	{
		free(arg->threads);
		free(arg->mutex_tab);
		free(arg->philo_tabstruct);
	}
}

void	destroy_mutex(t_arg *arg, int j)
{
	int	i;

	i = -1;
	if (j == 1 || j == 2 || j == 3 || j == 4)
	{
		while (++i < arg->nbr_philo)
			pthread_mutex_destroy(&arg->mutex_tab[i]);
	}
	if (j == 2 || j == 3 || j == 4)
		pthread_mutex_destroy(&arg->print_lock);
	if (j == 3 || j == 4)
		pthread_mutex_destroy(&arg->check_dead);
	if (j == 4)
		pthread_mutex_destroy(&arg->last_time_eat);
}
