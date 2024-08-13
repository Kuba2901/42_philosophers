/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 20:00:29 by jnenczak          #+#    #+#             */
/*   Updated: 2024/08/13 18:41:14 by jnenczak         ###   ########.fr       */
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

// Function to get the time since last meal
long	get_time_since_last_meal(t_philo *philo)
{
	return ((get_sim_runtime(*philo->simulation_start).tv_usec * 1000) - philo->last_meal);
}

void	pick_up_forks(t_philo *philo)
{
	int	left_index;
	int	right_index;

	left_index = philo->left->index;
	right_index = philo->right->index;
	if (left_index < right_index)
	{
		pthread_mutex_lock(&philo->left->lock);
		printf("Philo (%ld) has just picked up the left fork!\n", philo->index);
		pthread_mutex_lock(&philo->right->lock);
		printf("Philo (%ld) has just picked up the right fork!\n", philo->index);
	}
	else
	{
		pthread_mutex_lock(&philo->right->lock);
		printf("Philo (%ld) has just picked up the right fork!\n", philo->index);
		pthread_mutex_lock(&philo->left->lock);
		printf("Philo (%ld) has just picked up the left fork!\n", philo->index);

	}
}

void	put_down_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->left->lock);
	printf("Philo (%ld) has just put down the left fork!\n", philo->index);
	pthread_mutex_unlock(&philo->right->lock);
	printf("Philo (%ld) has just put down the right fork!\n", philo->index);
}

void	philo_sleep(t_philo *philo)
{
	philo->activity = SLEEPING;
	print_philo_state(*philo);
	sleep(*philo->time_to_sleep);
}

void	think(t_philo *philo)
{
	philo->activity = THINKING;
	print_philo_state(*philo);
	sleep(*philo->time_to_sleep);
	printf("Done sleeping\n");
}

void	eat(t_philo *philo)
{
	if (get_time_since_last_meal(philo) > *philo->time_to_die)
	{
		printf("Philo (%ld) has died of starvation :(\n", philo->index);
		*philo->is_dead = TRUE;
	}
	philo->activity = EATING;
	print_philo_state(*philo);
	sleep(*philo->time_to_eat);
	philo->last_meal = get_sim_runtime(*philo->simulation_start).tv_usec;
}

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
		current->is_over = &super->is_over;
		current->number_of_philo = &super->number_of_philo;
		current->time_to_die = &super->time_to_die;
		current->time_to_eat = &super->time_to_eat;
		current->time_to_sleep = &super->time_to_sleep;
		current->simulation_start = &super->simulation_start;
		current->is_dead = &super->has_error;
        ret[i] = current;
    }
    return (ret);
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
        if (ret[i] == NULL) {
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
