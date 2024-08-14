/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 19:11:36 by jnenczak          #+#    #+#             */
/*   Updated: 2024/08/14 18:33:48 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

// Thread function for the philosopher
void *philo_routine(t_philo *philo) {
    while (!(philo->is_over) && !(*philo->is_dead)) {
		long last_meal_delta = get_time_since_last_meal(philo);
		if (last_meal_delta > *philo->time_to_die)
		{	
			printf("%ld %ld died\n", ft_get_current_time(), philo->index);
			*philo->is_dead = TRUE;
			return NULL;
		}
		pick_up_forks(philo);
		eat(philo);
		put_down_forks(philo);
        think(philo);
		philo_sleep(philo);
    }
    
    return NULL;
}

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
	int	i = -1;
	while (++i < super->number_of_philo)
		pthread_create(&super->philos[i]->thread, NULL, (void *)philo_routine, super->philos[i]);
	i = -1;
	while (++i < super->number_of_philo)
		pthread_join(super->philos[i]->thread, NULL);
	free_resources(super);
	return (0);
}