/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 17:04:01 by jnenczak          #+#    #+#             */
/*   Updated: 2024/08/19 19:30:39 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

struct timeval	get_sim_runtime(struct timeval start)
{
	struct timeval	ret;
	struct timeval	tv_now;
	struct timezone	tz_now;

	gettimeofday(&tv_now, &tz_now);
	ret.tv_sec = tv_now.tv_sec - start.tv_sec;
	ret.tv_usec = tv_now.tv_usec - start.tv_usec;
	return (ret);
}

unsigned long	get_sim_runtime_milliseconds(struct timeval simulation_start)
{
	unsigned long	current_time;
	
	current_time = get_sim_runtime(simulation_start).tv_sec * 1000 + get_sim_runtime(simulation_start).tv_usec / 1000;
	return (current_time);
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