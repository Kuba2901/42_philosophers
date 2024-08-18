/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 20:15:36 by jnenczak          #+#    #+#             */
/*   Updated: 2024/08/18 20:17:47 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

t_supervisor	*parse_init_supervisor(int ac, char **av)
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
	if (!input_check_valid_number(av[1]) || !input_check_valid_number(av[2]) \
		|| !input_check_valid_number(av[3]) || !input_check_valid_number(av[4]))
	{
		free(ret);
		print_error("One of the arguments is not a number or is negative");
		exit(1);
	}
	return (ret);
}

t_supervisor	*parse_input(int ac, char **av)
{
	t_supervisor	*ret;

	ret = parse_init_supervisor(ac, av);
	init_supervisor_numbers(ret, av);
	if (ret->error)
	{
		free(ret);
		exit(1);
	}
	if (ac == 6)
	{
		if (!input_check_valid_number(av[5]))
		{
			free(ret);
			print_error("Optional argument is not a number");
			exit(1);
		}
		ret->number_of_meals = input_atoi_long(av[5]);
	}
	return (ret);
}
