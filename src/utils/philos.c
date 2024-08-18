/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 19:52:05 by jnenczak          #+#    #+#             */
/*   Updated: 2024/08/18 19:52:22 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static t_philo *init_single_philo(int i)
{
    t_philo *ret;
    
    ret = malloc(sizeof(t_philo));
    if (!ret)
    {
        print_error("Error initializing philosopher");
        return (NULL);
    }
    ret->activity = THINKING;
    ret->index = i + 1;
	ret->meals_eaten = 0;
	ret->is_full = FALSE;
    return (ret);
}

t_philo **init_philos(t_supervisor *super)
{
    int i;
    t_philo **ret;
    t_philo *current;

    ret = malloc(sizeof(t_philo *) * super->number_of_philo);
    if (!ret) {
        print_error("Error allocating philosophers array");
        return NULL;
    }
    i = -1;
    while (++i < super->number_of_philo)
    {
        current = init_single_philo(i);
        if (current == NULL)
        {
            free_until((void **)ret, i);
            return NULL;
        }
		current->number_of_philo = &super->number_of_philo;
		current->time_to_die = &super->time_to_die;
		current->time_to_eat = &super->time_to_eat;
		current->time_to_sleep = &super->time_to_sleep;
		current->simulation_start = &super->sim_start;
		current->last_meal = super->sim_start;
		current->number_of_meals_to_eat = &super->number_of_meals;
		pthread_mutex_init(&current->edit_lock, NULL);
		current->write_lock = &super->write_lock;
		current->dinner_over_lock = &super->dinner_over_lock;
		current->dead_lock = &super->dead_lock;
		current->error = &super->error;
		current->dinner_over = &super->dinner_over;
        ret[i] = current;
    }
    return (ret);
}