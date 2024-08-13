/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 19:11:36 by jnenczak          #+#    #+#             */
/*   Updated: 2024/08/12 18:48:00 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	print_philo_report(t_supervisor *super)
{
	int	i;

	i = -1;
	while (++i < super->number_of_philo)
		print_philo_state(*super->philos[i]);
}

int	main(int ac, char **av)
{
	t_supervisor	*super;

	super = NULL;
	super = parse_input(ac, av);
	super->forks = init_forks(super);
	if (super->forks == NULL)
	{
		free_resources(super);
		exit(1);
	}
	super->philos = init_philos(super);
	if (super->philos == NULL)
	{
		free_resources(super);
		exit(1);
	}
	assign_forks_to_philos(super);
	
	int		i;
    t_philo *philo;
    i = -1;
    while (++i < super->number_of_philo)
    {
        philo = super->philos[i];
        printf("Philo [%d]:\n", i);
        printf("    - left: %p\n", (void *)philo->left);
        printf("    - right: %p\n", (void *)philo->right);
    }
	debug_print_supervisor_data(*super);
	sleep(5);
	debug_print_supervisor_data(*super);
	print_philo_report(super);
	free_resources(super);
	return (0);
}