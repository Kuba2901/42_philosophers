/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 16:11:28 by jnenczak          #+#    #+#             */
/*   Updated: 2025/02/12 16:13:12 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

/* Header */
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
	printf(" %lu %ld %s\n", get_runtime_in_ms(philo),
		philo->index, get_activity_description(philo->activity));
	printf(RESET_COLOR);
}

static void	normal_print(t_philo *philo)
{
	printf("%lu %ld %s\n", get_runtime_in_ms(philo),
		philo->index, get_activity_description(philo->activity));
}

void	print_philo_state(t_philo *philo)
{
	t_bool	is_error;
	t_bool	is_dinner_over;

	is_dinner_over = check_dinner_over(philo);
	is_error = check_error(philo);
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
