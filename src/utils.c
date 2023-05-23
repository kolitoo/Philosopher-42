/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourdon <abourdon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 18:58:40 by abourdon          #+#    #+#             */
/*   Updated: 2023/05/23 19:00:04 by abourdon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ft_atoi(const char *str, int i)
{
	int	sign;
	int	nb;
	int	old_nb;

	i = 0;
	sign = 1;
	nb = 0;
	while (str[i] == ' ' || str[i] == '\f'
		|| str[i] == '\t' || str[i] == '\n' || str[i] == '\r' || str[i] == '\v')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		old_nb = nb;
		nb = nb * 10 + str[i] - 48;
		if (nb < old_nb)
			return (printf("Error: Atoi Overflow\n"), -1);
		i++;
	}
	return (sign * nb);
}

int	ft_is_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str [i] > '9')
			return (1);
		i++;
	}
	return (0);
}

long	ft_get_time(void)
{
	struct timeval	tv;
	long			res;

	gettimeofday(&tv, NULL);
	res = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (res);
}

void	ft_usleep(long int usec, t_philo *philo)
{
	long	time_action_start;

	(void)philo;
	time_action_start = ft_get_time();
	usleep(usec * 800);
	while (ft_get_time() - time_action_start < usec)
		usleep(usec / 10);
}

void	print_action(t_philo *philo, char *str, int bool)
{
	long int	time;

	time = ft_get_time() - philo->start_time;
	if (check_death(philo, 0) == 0)
	{
		if (bool == 1)
			printf("\033[0;31m");
		else if (bool == 2)
			printf("\033[0;33m");
		else if (bool == 3)
			printf("\033[0;35m");
		else if (bool == 4)
			printf("\033[0;34m");
		else
			printf("\033[0;37m");
		printf("%ld ", time);
		printf("%d %s\n\033[0;37m", philo->philo_id + 1, str);
	}
}
