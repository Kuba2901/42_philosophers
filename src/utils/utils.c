/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 19:07:11 by jnenczak          #+#    #+#             */
/*   Updated: 2024/08/19 18:31:33 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

const char	*get_activity_description(t_activity activity)
{
	if (activity == EATING)
		return ("is eating");
	else if (activity == SLEEPING)
		return ("is sleeping");
	else if (activity == THINKING)
		return ("is thinking");
	else if (activity == FORK)
		return ("has taken a fork");
	else
		return ("died");
}

unsigned long	get_runtime_in_ms(t_philo *philo)
{
	long	sim_start;
	long	runtime;

	sim_start = *philo->simulation_start;
	runtime = ft_get_current_time() - sim_start;
	return (runtime);
}

static void	pretty_print(t_philo *philo)
{
	if (philo->activity == THINKING)
		printf(GREEN_COLOR THINKING_EMOJI);
	else if (philo->activity == EATING)
		printf(YELLOW_COLOR EATING_EMOJI);
	else if (philo->activity == FORK)
		printf(YELLOW_COLOR FORK_EMOJI);
	else if (philo->activity == SLEEPING)
		printf(CYAN_COLOR SLEEPING_EMOJI);
	else if (philo->activity == DIED)
		printf(RED_COLOR DIED_EMOJI);
	printf(" %lu %ld %s\n", get_runtime_in_ms(philo), philo->index, get_activity_description(philo->activity));
	printf(RESET_COLOR);
}

static void	normal_print(t_philo *philo)
{
	printf("%lu %ld %s\n", get_runtime_in_ms(philo), philo->index, get_activity_description(philo->activity));
}

void	print_philo_state(t_philo *philo)
{
	t_bool			is_error;
	t_bool			is_dinner_over;

	is_dinner_over = check_dinner_over(philo);
	pthread_mutex_lock(philo->dead_lock);
	is_error = *philo->error;
	pthread_mutex_unlock(philo->dead_lock);
	if (!is_error && !is_dinner_over)
	{
		pthread_mutex_lock(philo->write_lock);
		if (PREETY_PRINT)
			pretty_print(philo);
		else
			normal_print(philo);
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

void free_until(void **elem, int i)
{
	int j;

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
