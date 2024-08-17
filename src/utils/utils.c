/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 19:07:11 by jnenczak          #+#    #+#             */
/*   Updated: 2024/08/17 19:52:30 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

const char	*get_activity_description(t_activity activity)
{
	if (activity == EATING)
		return "is eating";
	else if (activity == SLEEPING)
		return "is sleeping";
	else if (activity == THINKING)
		return "is thinking";
	else if (activity == FORK)
		return "has taken a fork";
	else
		return "died";
}

unsigned long	get_runtime_in_ms(t_philo *philo)
{
	long	sim_start;
	long	runtime;

	sim_start = *philo->simulation_start;
	runtime = ft_get_current_time() - sim_start;
	return (runtime);
}

void	print_philo_state(t_philo *philo)
{
	const char		*activity_description;
	t_bool			is_error;

	pthread_mutex_lock(philo->dead_lock);
	is_error = *philo->error;
	pthread_mutex_unlock(philo->dead_lock);
	if (!is_error)
	{
		pthread_mutex_lock(philo->write_lock);
		activity_description = get_activity_description(philo->activity);
		printf("%lu %ld %s\n", get_runtime_in_ms(philo), philo->index, activity_description);
		pthread_mutex_unlock(philo->write_lock);
	}
}

void	print_error(const char *err)
{
	int	i;
	int	len;

	i = 0;
	while (err[i])
	{
		len = write(STDERR_FILENO, &err[i], 1);
		if (len > 0)
			i++;
	}
	write(STDERR_FILENO, "\n", 1);
}

void	free_resources(t_supervisor *supervisor)
{
	int	i;

	if (supervisor != NULL)
	{
		if (supervisor->forks != NULL)
		{
			i = -1;
			while (++i < supervisor->number_of_philo)
				pthread_mutex_destroy(&supervisor->forks[i]->lock);
		}
		if (supervisor->philos != NULL)
		{
			i = -1;
			while (++i < supervisor->number_of_philo)
			{
				pthread_mutex_destroy(&supervisor->philos[i]->edit_lock);
				pthread_detach(supervisor->philos[i]->thread);
			}
		}
		free_until((void **)supervisor->forks, supervisor->number_of_philo);
		free_until((void **)supervisor->philos, supervisor->number_of_philo);
		pthread_detach(supervisor->thread);
		pthread_mutex_destroy(&supervisor->write_lock);
		pthread_mutex_destroy(&supervisor->dead_lock);
		pthread_mutex_destroy(&supervisor->dinner_over_lock);
		free(supervisor);
	}
}