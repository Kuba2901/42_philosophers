/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervisor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 16:07:01 by jnenczak          #+#    #+#             */
/*   Updated: 2025/02/12 16:13:22 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static long	*check_philo_status(t_supervisor *super, int i, long *full_philos)
{
	t_philo	*philo;
	long	last_meal_delta;

	philo = super->philos[i];
	if (philo->is_full)
	{
		*full_philos += 1;
		return (full_philos);
	}
	last_meal_delta = get_time_since_last_meal(philo);
	if (last_meal_delta >= *philo->time_to_die)
	{
		pthread_mutex_lock(&super->write_lock);
		pthread_mutex_lock(&super->dead_lock);
		printf("%ld %ld died\n", get_runtime_in_ms(philo), philo->index);
		super->error = TRUE;
		pthread_mutex_unlock(&super->dead_lock);
		return (NULL);
	}
	return (full_philos);
}

static int	handle_dinner_completion(t_supervisor *super)
{
	pthread_mutex_lock(&super->write_lock);
	pthread_mutex_lock(&super->dinner_over_lock);
	pthread_mutex_lock(&super->dead_lock);
	super->dinner_over = TRUE;
	super->error = TRUE;
	pthread_mutex_unlock(&super->dead_lock);
	pthread_mutex_unlock(&super->dinner_over_lock);
	pthread_mutex_unlock(&super->write_lock);
	printf("Dinner is over\n");
	return (1);
}

void	*supervisor_routine(t_supervisor *super)
{
	int		i;
	long	full_philos;

	while (!super->error)
	{
		i = -1;
		full_philos = 0;
		while (++i < super->number_of_philo)
		{
			if (check_philo_status(super, i, &full_philos) == NULL)
				return (NULL);
		}
		if (full_philos == super->number_of_philo)
			if (handle_dinner_completion(super))
				break ;
		usleep(100);
	}
	return (NULL);
}
