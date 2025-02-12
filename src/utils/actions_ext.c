/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_ext.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 15:57:10 by jnenczak          #+#    #+#             */
/*   Updated: 2025/02/12 15:57:20 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

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
