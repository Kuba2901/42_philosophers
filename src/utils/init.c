/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 20:00:29 by jnenczak          #+#    #+#             */
/*   Updated: 2024/08/06 20:31:26 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static void	free_previous(t_fork **forks, int i)
{
	int	j;

	j = -1;
	while (++j < i)
		free(forks[j]);
	free(forks);
}

t_fork	*init_forks(t_supervisor *super)
{
	int		i;
	t_fork	**ret;
	
	ret = malloc(sizeof(t_fork *) * super->number_of_philo);
	i = -1;
	while (++i < super->number_of_philo)
	{
		ret[i] = malloc(sizeof(t_fork));
		ret[i]->index = i;
		if (pthread_mutex_init(&ret[i]->lock, NULL) != 0)
		{
			print_error("Mutex INIT failed");
			free_previous(ret, i);
			return (NULL);
		}
	}
}