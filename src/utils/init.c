/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 20:00:29 by jnenczak          #+#    #+#             */
/*   Updated: 2024/08/06 20:56:08 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

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

// TEMP
// Thread function for the philosopher
void *philo_routine(void *arg) {
    t_philo *philo = (t_philo *)arg;
    
    while (1) {
        // Simulate thinking
        philo->activity = THINKING;
        printf("Philosopher %ld is thinking\n", philo->index);
        sleep(1);  // Simulate time taken for thinking
        
        // Simulate eating
        philo->activity = EATING;
        philo->last_meal = time(NULL);
        printf("Philosopher %ld is eating\n", philo->index);
        sleep(2);  // Simulate time taken for eating
        
        // Simulate sleeping
        philo->activity = SLEEPING;
        philo->last_sleep = time(NULL);
        printf("Philosopher %ld is sleeping\n", philo->index);
        sleep(1);  // Simulate time taken for sleeping
    }
    
    return NULL;
}

// /TEMP

static t_philo *init_single_philo(int i)
{
    t_philo *ret;
    
    ret = malloc(sizeof(t_philo));
    if (!ret)
    {
        print_error("Error initializing philosopher");
        return (NULL);
    }
    ret->activity = SLEEPING;
    ret->index = i + 1;
    ret->last_meal = 0;
    ret->last_sleep = 0;
    ret->last_thinking = 0;
    // if (pthread_create(&ret->thread, NULL, philo_routine, (void *)ret) != 0) {
    //     print_error("Error creating philosopher thread");
    //     free(ret);
    //     return NULL;
    // }
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
        ret[i] = current;
    }
    return ret;
}

t_fork **init_forks(t_supervisor *super)
{
    int		i;
    t_fork	**ret;
    
    ret = malloc(sizeof(t_fork *) * super->number_of_philo);
    if (!ret) {
        print_error("Error allocating forks array");
        return (NULL);
    }
    i = -1;
    while (++i < super->number_of_philo)
    {
        ret[i] = malloc(sizeof(t_fork));
        if (!ret[i]) {
            print_error("Error allocating fork");
            free_until((void **)ret, i);
            return (NULL);
        }
        ret[i]->index = i;
        if (pthread_mutex_init(&ret[i]->lock, NULL) != 0)
        {
            print_error("Mutex INIT failed");
            free_until((void **)ret, i);
            return (NULL);
        }
    }
    return (ret);
}
