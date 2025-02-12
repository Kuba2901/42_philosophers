/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 16:12:00 by jnenczak          #+#    #+#             */
/*   Updated: 2025/02/12 16:13:10 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

/* Header */
#include <philo.h>

unsigned long	get_runtime_in_ms(t_philo *philo)
{
	long	sim_start;
	long	runtime;

	sim_start = *philo->simulation_start;
	runtime = ft_get_current_time() - sim_start;
	return (runtime);
}

unsigned long	get_time_since_last_meal(t_philo *philo)
{
	return (ft_get_current_time() - philo->last_meal);
}

unsigned long	ft_get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		print_error("Error getting current time");
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	ft_usleep(unsigned long milliseconds)
{
	unsigned long	start;

	start = ft_get_current_time();
	while ((ft_get_current_time() - start) < milliseconds)
		usleep(100);
	return (0);
}
