/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_destroy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourdon <abourdon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 12:09:54 by abourdon          #+#    #+#             */
/*   Updated: 2023/05/01 21:43:51 by abourdon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	free_all(t_arg *arg)
{
	free(arg->threads);
	free(arg->mutex_tab);
	free(arg->philo_tabstruct);
}

void	unlock_and_destroy_mutex(t_arg *arg, int j)
{
	int	i;

	i = -1;
	if (j == 1 || j == 2 || j == 3)
	{
		while (++i < arg->nbr_philo)
			pthread_mutex_destroy(&arg->mutex_tab[i]);
	}
	if (j == 2 || j == 3)
		pthread_mutex_destroy(&arg->print_lock);
	if (j == 3)
		pthread_mutex_destroy(&arg->check_died);
}
