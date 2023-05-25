/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourdon <abourdon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 18:36:53 by abourdon          #+#    #+#             */
/*   Updated: 2023/05/17 19:43:58 by abourdon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

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
	if (ft_init_thread(&arg, -1, -1, -1) == 1)
		return (1);
	free_and_destroy(&arg);
	return (0);
}
