/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 19:07:11 by jnenczak          #+#    #+#             */
/*   Updated: 2024/08/07 16:44:57 by jnenczak         ###   ########.fr       */
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

void	print_philo_state(t_philo philo)
{
	const char	*activity_description;

	activity_description = get_activity_description(philo.activity);
	printf("%ld %ld %s\n", philo.last_meal, philo.index, activity_description);
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
		free_until((void **)supervisor->forks, supervisor->number_of_philo);
		free_until((void **)supervisor->philos, supervisor->number_of_philo);
		free(supervisor);
	}
}

void	debug_print_supervisor_data(t_supervisor supervisor)
{
	printf("[*] SUPERVISOR DATA\n");
	printf("number_of_philo: %ld\n", supervisor.number_of_philo);
	printf("time_to_die: %ld\n", supervisor.time_to_die);
	printf("time_to_eat: %ld\n", supervisor.time_to_eat);
	printf("time_to_sleep: %ld\n", supervisor.time_to_sleep);
	printf("number_of_meals: %ld\n", supervisor.number_of_meals);
	printf("\n");
}