/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 19:19:18 by jnenczak          #+#    #+#             */
/*   Updated: 2024/08/17 19:52:36 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static int	is_not_just_whitespace_and_sign(const char *str)
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

static long	custom_strtol(const char *str, char **endptr)
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

static int	is_valid_number(const char *str)
{
	long	val;
	char	*endptr;

	if (*str == '\0')
		return (0);
	if (!is_not_just_whitespace_and_sign(str))
		return (0);
	val = custom_strtol(str, &endptr);
	return (*endptr == '\0' && val >= 0);
}

long	custom_atoi_long(const char *str)
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

static void	init_supervisor(t_supervisor *super)
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

t_supervisor	*parse_input(int ac, char **av)
{
	t_supervisor	*ret;

	if (ac < 5 || ac > 6)
	{
		print_error("Wrong number of arguments - should be 4[5]");
		exit(1);
	}
	ret = malloc(sizeof(t_supervisor));
	if (!ret)
		exit(1);
	init_supervisor(ret);
	if (!is_valid_number(av[1]) || !is_valid_number(av[2]) \
		|| !is_valid_number(av[3]) || !is_valid_number(av[4]))
	{
		free(ret);
		print_error("One of the arguments is not a number or is negative");
		exit(1);
	}
	init_supervisor_numbers(ret, av);
	if (ret->error)
	{
		free(ret);
		exit(1);
	}
	if (ac == 6)
	{
		if (!is_valid_number(av[5]))
		{
			free(ret);
			print_error("Optional argument is not a number");
			exit(1);
		}
		ret->number_of_meals = custom_atoi_long(av[5]);
	}
	return (ret);
}