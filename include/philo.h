/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourdon <abourdon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 18:36:26 by abourdon          #+#    #+#             */
/*   Updated: 2023/04/15 12:35:04 by abourdon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>

typedef struct s_arg
{
	int				nbr_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_time_must_eat;
	int				nb_philo;
	pthread_mutex_t	*forks;
	pthread_mutex_t	lock;
}	t_arg;

int	ft_is_digit(char *str);
int	ft_atoi(const char *str);
int	ft_init_args(int ac, char **av, t_arg *arg);
int	ft_init_mutex(t_arg *arg);
void	free_all(t_arg *arg);
void	destroy_mutex(t_arg *args);

#endif