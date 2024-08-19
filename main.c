/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 19:11:36 by jnenczak          #+#    #+#             */
/*   Updated: 2024/08/19 18:31:45 by jnenczak         ###   ########.fr       */
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

	i = -1;
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
				if (last_meal_delta >= *philo->time_to_die) // (>=)
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
			// pthread_mutex_lock(&super->write_lock); // BLOCKS THE EXIT OF THE PROGRAM
			printf("Dinner is over\n");
			break ;
		}
		usleep(100);
	}
	return (NULL);
}

t_bool	check_dinner_over(t_philo *philo)
{
	t_bool	is_dinner_over;
	
	pthread_mutex_lock(philo->dinner_over_lock);
	is_dinner_over = *philo->dinner_over;
	pthread_mutex_unlock(philo->dinner_over_lock);
	return (is_dinner_over);
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
	if (philo->index % 2 == 0)
		ft_usleep(*philo->time_to_sleep / 2);
    while (!check_error(philo) && !check_dinner_over(philo))
    {
        if (check_error(philo) || check_dinner_over(philo))
			break;
        action_think(philo);
        if (check_error(philo) || check_dinner_over(philo))	
			break;
        action_pick_up_forks(philo);
        if (check_error(philo) || check_dinner_over(philo)) {
            action_put_down_forks(philo);
            break;
        }
        action_eat(philo);
        action_put_down_forks(philo);
        if (check_error(philo) || check_dinner_over(philo))	
			break;
        action_sleep(philo);
		if (*philo->number_of_philo % 2 != 0)
			ft_usleep(*philo->time_to_sleep / 3);
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
	super->sim_start = 0;
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
	assign_forks(super);
	int	i = -1;
	super->sim_start = ft_get_current_time();
	while (++i < super->number_of_philo)
		pthread_create(&super->philos[i]->thread, NULL, (void *)philo_routine, super->philos[i]);
	pthread_create(&super->thread, NULL, (void *)supervisor_routine, super);
	i = -1;
	while (++i < super->number_of_philo)
	{
		super->philos[i]->last_meal = super->sim_start;
		super->philos[i]->simulation_start = &super->sim_start;
	}
	i = -1;
	while (++i < super->number_of_philo)
		pthread_join(super->philos[i]->thread, NULL);
	pthread_join(super->thread, NULL);
	free_resources(super);
	return (0);
}