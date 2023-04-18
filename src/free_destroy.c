/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_destroy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourdon <abourdon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 12:09:54 by abourdon          #+#    #+#             */
/*   Updated: 2023/04/15 12:34:55 by abourdon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	free_all(t_arg *arg)
{
	free(arg->forks);
}

void	destroy_mutex(t_arg *args)
{
	int	nb;

	nb = args->nbr_philo;
	while (nb)
	{
		pthread_mutex_unlock(&arg->forks[nb]);
		pthread_mutex_destroy(&arg->forks[nb]);
		nb--;
	}
	pthread_mutex_unlock(&arg->lock);
	pthread_mutex_destroy(&arg->lock);
}