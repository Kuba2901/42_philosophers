/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 19:11:36 by jnenczak          #+#    #+#             */
/*   Updated: 2024/08/17 16:33:28 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

// Thread function for the supervisor
void	*supervisor_routine(t_supervisor *super)
{
	int		i;
	t_philo	*philo;
	long	last_meal_delta;

	while (!super->has_error)
	{
		i = -1;
		while (++i < super->number_of_philo)
		{
			philo = super->philos[i];
			last_meal_delta = get_time_since_last_meal(philo);
			if (last_meal_delta > *philo->time_to_die)
			{	
				printf("%ld %ld died\n", get_runtime_in_ms(philo), philo->index);
				*philo->is_dead = TRUE;
				return (NULL);
			}
		}
	}

	return (NULL);
}

// Thread function for the philosopher
void	*philo_routine(t_philo *philo) {
    while (!(philo->is_full) && !(*philo->is_dead)) {
        think(philo);
		pick_up_forks(philo);
		eat(philo);
		put_down_forks(philo);
		philo_sleep(philo);
    }
    
    return (NULL);
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
	pthread_create(&super->thread, NULL, (void *)supervisor_routine, super);
	pthread_join(super->thread, NULL);
	i = -1;
	while (++i < super->number_of_philo)
		pthread_join(super->philos[i]->thread, NULL);
	free_resources(super);
	return (0);
}