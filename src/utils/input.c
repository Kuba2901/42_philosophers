/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 19:19:18 by jnenczak          #+#    #+#             */
/*   Updated: 2024/08/18 20:27:06 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	input_check_empty(const char *str)
{
	int	i;
	int	contains_digits;

	i = 0;
	contains_digits = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			contains_digits = 1;
		i++;
	}
	return (contains_digits);
}

long	input_strtol(const char *str, char **endptr)
{
	long	result;
	int		sign;

	result = 0;
	sign = 1;
	while (*str == ' ' || *str == '\t')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	if (endptr)
		*endptr = (char *)str;
	return (sign * result);
}

int	input_check_valid_number(const char *str)
{
	long	val;
	char	*endptr;

	if (*str == '\0')
		return (0);
	if (!input_check_empty(str))
		return (0);
	val = input_strtol(str, &endptr);
	return (*endptr == '\0' && val >= 0);
}

long	input_atoi_long(const char *str)
{
	long	result;
	int		sign;

	result = 0;
	sign = 1;
	while (*str == ' ' || *str == '\t')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	return (sign * result);
}

void	init_supervisor(t_supervisor *super)
{
	super->forks = NULL;
	super->philos = NULL;
	super->number_of_meals = 0;
	super->number_of_philo = 0;
	super->time_to_die = 0;
	super->time_to_eat = 0;
	super->time_to_sleep = 0;
	pthread_mutex_init(&super->dead_lock, NULL);
	pthread_mutex_init(&super->write_lock, NULL);
	pthread_mutex_init(&super->dinner_over_lock, NULL);
}
