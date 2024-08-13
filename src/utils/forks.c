/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 17:44:28 by jnenczak          #+#    #+#             */
/*   Updated: 2024/08/12 18:43:35 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	assign_forks_to_philos(t_supervisor *super)
{
	long	i;
	t_philo	*philo;

	i = 0;
	while (i < super->number_of_philo)
	{
		philo = super->philos[i];
		philo->left = super->forks[i];
		philo->right = super->forks[(i + 1) % super->number_of_philo];
		i++;
	}
}
