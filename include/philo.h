/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourdon <abourdon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 18:36:26 by abourdon          #+#    #+#             */
/*   Updated: 2023/04/21 16:22:58 by abourdon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <pthread.h>
# include <unistd.h>

typedef struct s_philo
{
	int				philo_id;
	int				nbr_philo;
	int				total_nbr_of_must_eat;
	int				time_to_eat;
	int				time_to_die;
	int				time_to_sleep;
	long			time_of_last_must_eat;
	long			start_time;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	print_lock;
	struct s_arg	*arg;
}	t_philo;

typedef struct s_arg
{
	int				nbr_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_time_must_eat;
	int				philo_id;
	pthread_mutex_t		*mutex_tab;
	pthread_mutex_t		print_lock;
	pthread_t		*threads;
	t_philo			*philo_tabstruct;
}	t_arg;

int		ft_is_digit(char *str);
int		ft_atoi(const char *str);
int		ft_init_args(int ac, char **av, t_arg *arg);
int		ft_check_values(int ac, t_arg *arg, char **av);
int		ft_check_arg(int ac, char **av);
int		ft_init_thread(t_arg *arg);
int		ft_init_philo(t_arg *arg);
int		ft_init_mutex(t_arg *arg);
void	free_all(t_arg *arg);
void	*thread_routine(void *arg);
void	printphilo(t_arg *arg);
void	take_fork(t_philo *philo);
void	eating(t_philo *philo);
void	sleeping(t_philo *philo);
void	thinking(t_philo *philo);
void	unlock_and_destroy_mutex(t_arg *arg);
void	ft_usleep(int usec);
void	*ft_test(void *arg);
long	ft_get_time(void);

#endif