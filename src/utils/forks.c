/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 17:44:28 by jnenczak          #+#    #+#             */
/*   Updated: 2024/08/18 19:58:05 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	assign_forks(t_supervisor *super)
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

t_fork	**init_forks(t_supervisor *super)
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
            free_until((void **)ret, i);
            return (NULL);
        }
        ret[i]->index = i;
        if (pthread_mutex_init(&(ret[i]->lock), NULL) != 0)
        {
            free_until((void **)ret, i);
            return (NULL);
        }
    }
    return (ret);
}
