/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 19:11:36 by jnenczak          #+#    #+#             */
/*   Updated: 2025/02/12 16:09:36 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static int	handle_actions(t_philo *philo)
{
	if (check_error(philo) || check_dinner_over(philo))
		return (0);
	action_think(philo);
	if (check_error(philo) || check_dinner_over(philo))
		return (0);
	action_pick_up_forks(philo);
	if (check_error(philo) || check_dinner_over(philo))
	{
		action_put_down_forks(philo);
		return (0);
	}
	action_eat(philo);
	action_put_down_forks(philo);
	if (check_error(philo) || check_dinner_over(philo))
		return (0);
	action_sleep(philo);
	return (1);
}

void	*philo_routine(t_philo *philo)
{
	if (philo->index % 2 == 0)
		ft_usleep(*philo->time_to_sleep / 2);
	while (!check_error(philo) && !check_dinner_over(philo))
	{
		if (!handle_actions(philo))
			break ;
		if (*philo->number_of_philo % 2 != 0)
			ft_usleep(*philo->time_to_sleep / 3);
	}
	return (NULL);
}

static void	init_philosopher_times(t_supervisor *super)
{
	int	i;

	i = -1;
	while (++i < super->number_of_philo)
	{
		super->philos[i]->last_meal = super->sim_start;
		super->philos[i]->simulation_start = &super->sim_start;
	}
}

t_supervisor	*init(int ac, char **av)
{
	t_supervisor	*super;

	super = parse_input(ac, av);
	super->forks = init_forks(super);
	super->error = FALSE;
	if (super->forks == NULL)
	{
		free_resources(super);
		exit(1);
	}
	super->philos = init_philos(super);
	if (super->philos == NULL)
	{
		free_resources(super);
		exit(1);
	}
	assign_forks(super);
	super->sim_start = ft_get_current_time();
	init_philosopher_times(super);
	return (super);
}

int	main(int ac, char **av)
{
	t_supervisor	*super;
	int				i;

	i = -1;
	super = init(ac, av);
	while (++i < super->number_of_philo)
		pthread_create(&super->philos[i]->thread, NULL,
			(void *)philo_routine, super->philos[i]);
	pthread_create(&super->thread, NULL,
		(void *)supervisor_routine, super);
	i = -1;
	while (++i < super->number_of_philo)
		pthread_join(super->philos[i]->thread, NULL);
	pthread_join(super->thread, NULL);
	free_resources(super);
	return (0);
}
