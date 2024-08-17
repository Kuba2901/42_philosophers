/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 19:11:36 by jnenczak          #+#    #+#             */
/*   Updated: 2024/08/17 19:24:11 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

// Thread function for the supervisor
void	*supervisor_routine(t_supervisor *super)
{
	int		i;
	int		full_philos;
	t_philo	*philo;
	long	last_meal_delta;

	gettimeofday(&super->simulation_start, NULL);
	while (!super->error)
	{
		i = -1;
		full_philos = 0;
		while (++i < super->number_of_philo)
		{
			philo = super->philos[i];
			if (philo->is_full)
				full_philos++;
			else
			{
				last_meal_delta = get_time_since_last_meal(philo);
				if (last_meal_delta >= *philo->time_to_die) // TODO : Verify if should not be (>=)
				{   
					pthread_mutex_lock(&super->dead_lock);
					pthread_mutex_lock(&super->write_lock);
					printf("%ld %ld died\n", get_runtime_in_ms(philo), philo->index);
					super->error = TRUE;
					pthread_mutex_unlock(&super->dead_lock);
					return (NULL);
				}
			}
		}
		if (full_philos == super->number_of_philo)
		{
			pthread_mutex_lock(&super->dinner_over_lock);
			super->dinner_over = TRUE;
			pthread_mutex_unlock(&super->dinner_over_lock);
			pthread_mutex_lock(&super->write_lock);
			printf("Dinner is over\n");
			pthread_mutex_unlock(&super->write_lock);
			break ;
		}
		ft_usleep(1000);
	}
	return (NULL);
}


t_bool	check_error(t_philo *philo)
{
	t_bool	is_error;
	
	pthread_mutex_lock(philo->dead_lock);
	is_error = *philo->error;
	pthread_mutex_unlock(philo->dead_lock);
	return (is_error);
}

// Thread function for the philosopher
void *philo_routine(t_philo *philo)
{
    while (!philo->is_full && !check_error(philo))
    {
        if (check_error(philo)) break;
        think(philo);
        if (check_error(philo)) break;
        pick_up_forks(philo);
        if (check_error(philo)) {
            put_down_forks(philo);
            break;
        }
        eat(philo);
        put_down_forks(philo);
        if (check_error(philo)) break;
        philo_sleep(philo);
    }
    return (NULL);
}

void	print_philo_report(t_supervisor *super)
{
	int	i;

	i = -1;
	while (++i < super->number_of_philo)
		print_philo_state(super->philos[i]);
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
	i = -1;
	while (++i < super->number_of_philo)
		pthread_join(super->philos[i]->thread, NULL);
	pthread_join(super->thread, NULL);
	while (++i < super->number_of_philo)
	{
		pthread_mutex_lock(&super->philos[i]->left->lock);
		pthread_mutex_unlock(&super->philos[i]->left->lock);
	}
	free_resources(super);
	return (0);
}