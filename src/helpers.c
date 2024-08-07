/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 17:04:01 by jnenczak          #+#    #+#             */
/*   Updated: 2024/08/07 17:08:59 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

struct timeval	get_sim_runtime(t_supervisor *super)
{
	struct timeval	ret;
	struct timeval	tv_now;
	struct timezone	tz_now;

	gettimeofday(&tv_now, &tz_now);
	ret.tv_sec = tv_now.tv_sec - super->simulation_start.tv_sec;
	ret.tv_usec = tv_now.tv_usec - super->simulation_start.tv_usec;
	return (ret);
}