/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 20:00:29 by jnenczak          #+#    #+#             */
/*   Updated: 2024/08/18 20:12:09 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	action_pick_up_forks(t_philo *philo)
{
	if (*philo->number_of_philo == 1)
	{
		ft_usleep(*philo->time_to_die);
		pthread_mutex_lock(philo->dead_lock);
		*philo->error = TRUE;
		pthread_mutex_unlock(philo->dead_lock);
		return ;
	}
	philo->activity = FORK;
	if (philo->left->index < philo->right->index)
	{
		pthread_mutex_lock(&philo->left->lock);
		print_philo_state(philo);
		pthread_mutex_lock(&philo->right->lock);
		print_philo_state(philo);
	}
	else
	{
		pthread_mutex_lock(&philo->right->lock);
		print_philo_state(philo);
		pthread_mutex_lock(&philo->left->lock);
		print_philo_state(philo);
	}
}

void	action_put_down_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->left->lock);
	pthread_mutex_unlock(&philo->right->lock);
}

void	action_sleep(t_philo *philo)
{
	philo->activity = SLEEPING;
	print_philo_state(philo);
	ft_usleep(*philo->time_to_sleep);
}

void	action_think(t_philo *philo)
{
	philo->activity = THINKING;
	print_philo_state(philo);
}

void	action_eat(t_philo *philo)
{
	philo->activity = EATING;
	philo->last_meal = ft_get_current_time();
	print_philo_state(philo);
	ft_usleep(*philo->time_to_eat);
	philo->meals_eaten++;
	if (*philo->number_of_meals_to_eat && \
			philo->meals_eaten >= *philo->number_of_meals_to_eat)
		philo->is_full = TRUE;
}
