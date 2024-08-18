/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 19:52:05 by jnenczak          #+#    #+#             */
/*   Updated: 2024/08/18 20:20:20 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static t_philo	*init_single_philo(int i)
{
	t_philo	*ret;

	ret = malloc(sizeof(t_philo));
	if (!ret)
	{
		print_error("Error initializing philosopher");
		return (NULL);
	}
	ret->activity = THINKING;
	ret->index = i + 1;
	ret->meals_eaten = 0;
	ret->is_full = FALSE;
	return (ret);
}

static void	init_single_philo_pointers(t_supervisor *super, t_philo *philo)
{
	philo->number_of_philo = &super->number_of_philo;
	philo->time_to_die = &super->time_to_die;
	philo->time_to_eat = &super->time_to_eat;
	philo->time_to_sleep = &super->time_to_sleep;
	philo->simulation_start = &super->sim_start;
	philo->last_meal = super->sim_start;
	philo->number_of_meals_to_eat = &super->number_of_meals;
	pthread_mutex_init(&philo->edit_lock, NULL);
	philo->write_lock = &super->write_lock;
	philo->dinner_over_lock = &super->dinner_over_lock;
	philo->dead_lock = &super->dead_lock;
	philo->error = &super->error;
	philo->dinner_over = &super->dinner_over;
}

t_philo	**init_philos(t_supervisor *super)
{
	int		i;
	t_philo	**ret;
	t_philo	*current;

	ret = malloc(sizeof(t_philo *) * super->number_of_philo);
	if (!ret)
	{
		print_error("Error allocating philosophers array");
		return (NULL);
	}
	i = -1;
	while (++i < super->number_of_philo)
	{
		current = init_single_philo(i);
		if (current == NULL)
		{
			free_until((void **)ret, i);
			return (NULL);
		}
		init_single_philo_pointers(super, current);
		ret[i] = current;
	}
	return (ret);
}
