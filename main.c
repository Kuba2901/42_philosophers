/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 19:11:36 by jnenczak          #+#    #+#             */
/*   Updated: 2024/08/06 20:53:03 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	main(int ac, char **av)
{
	t_supervisor	*super;

	super = NULL;
	super = parse_input(ac, av);
	init_forks(super);
	if (super->forks == NULL)
	{
		free_resources(super);
		exit(1);
	}
	init_philos(super);
	if (super->philos == NULL)
	{
		free_resources(super);
		exit(1);
	}
	debug_print_supervisor_data(*super);
	free_resources(super);
	return (0);
}