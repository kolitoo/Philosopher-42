/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_destroy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourdon <abourdon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 12:09:54 by abourdon          #+#    #+#             */
/*   Updated: 2023/05/15 18:20:51 by abourdon         ###   ########.fr       */
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
	(void)j;
	int	i;

	i = -1;
	while (++i < arg->nbr_philo)
		pthread_mutex_destroy(&arg->mutex_tab[i]);
	pthread_mutex_destroy(&arg->print_lock);
	pthread_mutex_destroy(&arg->check_dead);
	pthread_mutex_destroy(&arg->last_time_eat);
}
