/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_destroy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourdon <abourdon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 12:09:54 by abourdon          #+#    #+#             */
/*   Updated: 2023/05/01 19:04:24 by abourdon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	free_all(t_arg *arg)
{
	free(arg->threads);
	free(arg->mutex_tab);
	free(arg->philo_tabstruct);
}

void	unlock_and_destroy_mutex(t_arg *arg)
{
	int	i;

	i = arg->nbr_philo;
	while (i--)
	{
		// if (arg->mutex_lock == 1)
		// 	pthread_mutex_unlock(&arg->mutex_tab[i]);
		// pthread_mutex_destroy(&arg->mutex_tab[i]);
	}
	// pthread_mutex_unlock(&(*arg).print_lock);
	pthread_mutex_destroy(&(*arg).print_lock);
	// pthread_mutex_unlock(&(*arg).check_died);
	// pthread_mutex_destroy(&(*arg).check_died);
}
