/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourdon <abourdon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 18:36:26 by abourdon          #+#    #+#             */
/*   Updated: 2023/05/23 12:55:56 by abourdon         ###   ########.fr       */
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
	int				actual_meals;
	int				time_to_eat;
	int				time_to_die;
	int				time_to_sleep;
	int				stop;
	long			time_of_last_must_eat;
	long			start_time;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
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
	int				dead;
	int				count_meals;
	int				flag;
	pthread_mutex_t	*mutex_tab;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	last_time_eat;
	pthread_mutex_t	check_dead;
	pthread_t		*threads;
	t_philo			*philo_tabstruct;
}	t_arg;

/*free_destroy.c*/
void	free_and_destroy(t_arg *arg);
void	free_all(t_arg *arg, int i);
void	destroy_mutex(t_arg *arg, int i);

/*action.c*/
void	take_fork(t_philo *philo);
void	eating(t_philo *philo);
void	sleeping(t_philo *philo);
void	thinking(t_philo *philo);

/*check.c*/
int		ft_check_values(int ac, t_arg *arg, char **av);
int		ft_check_arg(int ac, char **av);

/*init_args_and_philo.c*/
int		ft_init_args(int ac, char **av, t_arg *arg);
int		ft_init_philo(t_arg *arg);

/*init_process.c*/
int		ft_init_thread(t_arg *arg, int i, int j, int k);
int		ft_init_mutex(t_arg *arg);

/*routine.c*/
int		check_death(t_philo *philo, int i);
int		check_loop(t_philo *philo);
int		check_meals(t_philo *philo);
void	*thread_routine(void *arg);

/*utils.c*/
int		ft_is_digit(char *str);
int		ft_atoi(const char *str, int i);
void	ft_usleep(long int usec, t_philo *philo);
void	print_action(t_philo *philo, char *str, int bool);
long	ft_get_time(void);
void	*test_check(void *arg);

#endif