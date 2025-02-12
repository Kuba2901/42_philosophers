/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 16:12:15 by jnenczak          #+#    #+#             */
/*   Updated: 2025/02/12 16:13:08 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

/* Header */
#include <philo.h>

void	free_until(void **elem, int i)
{
	int	j;

	if (elem != NULL)
	{
		j = -1;
		while (++j < i)
		{
			if (elem[j] != NULL)
				free(elem[j]);
		}
		free(elem);
	}
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
				pthread_mutex_destroy(&supervisor->philos[i]->edit_lock);
		}
		free_until((void **)supervisor->forks, supervisor->number_of_philo);
		free_until((void **)supervisor->philos, supervisor->number_of_philo);
		pthread_mutex_destroy(&supervisor->write_lock);
		pthread_mutex_destroy(&supervisor->dead_lock);
		pthread_mutex_destroy(&supervisor->dinner_over_lock);
		pthread_detach(supervisor->thread);
		free(supervisor);
	}
}
