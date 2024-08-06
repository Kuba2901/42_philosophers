/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_checks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 20:14:23 by jnenczak          #+#    #+#             */
/*   Updated: 2024/08/06 20:22:51 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static void	assign_number_of_philo(t_supervisor *super, char *str)
{
	long	ret;

	ret = custom_atoi_long(str);
	if (ret < 1)
	{
		print_error("The number of philosophers has to be > 0");
		super->has_error = TRUE;
	}
	super->number_of_philo = ret;
}

static void	assign_time_to_eat(t_supervisor *super, char *str)
{
	long	ret;

	ret = custom_atoi_long(str);
	if (ret < 1)
	{
		print_error("The time to eat > 1");
		super->has_error = TRUE;
	}
	super->time_to_eat = ret;
}

static void	assign_time_to_sleep(t_supervisor *super, char *str)
{
	long	ret;

	ret = custom_atoi_long(str);
	if (ret < 0)
	{
		print_error("The number of philosophers has to be >= 0");
		super->has_error = TRUE;
	}
	super->time_to_eat = ret;
}

static void	assign_time_to_die(t_supervisor *super, char *str)
{
	long	ret;

	ret = custom_atoi_long(str);
	if (ret < 1)
	{
		print_error("The time to die has to be > 0");
		super->has_error = TRUE;
	}
	super->time_to_die = ret;
}

void	init_supervisor_numbers(t_supervisor *super, char **av)
{
	assign_number_of_philo(super, av[1]);
	assign_time_to_eat(super, av[2]);
	assign_time_to_die(super, av[3]);
	assign_time_to_sleep(super, av[4]);
}