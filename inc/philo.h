#ifndef PHILO_H
# define PHILO_H
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>
#include <stdlib.h>
#include <limits.h>

typedef enum s_bool
{
	TRUE,
	FALSE
}	t_bool;

typedef enum s_activity
{
	EATING,
	SLEEPING,
	THINKING,
	DIED,
	FORK

}	t_activity;

typedef struct s_supervisor
{
	long	number_of_philo; // Total number of philosophers
	long	time_to_die; // The max time between meals (or the beginning of the simulation and the first meal)
	long	time_to_eat; // The time it takes the philosopher to eat
	long	time_to_sleep; // The time it takes the philosopher to sleep
	long	number_of_meals; // The number of meals each philosopher has to eat before the end of simulation (-1 means INF)
	t_bool	has_error;
}	t_supervisor;

typedef struct s_philo
{
	long	index; // Starting with 1
	long	last_meal; // TS
	t_activity	activity; // Current philosopher activity
}	t_philo;

const char		*get_activity_description(t_activity activity);
void			print_philo_state(t_philo philo);
void			print_error(const char *err);
void			free_resources(t_supervisor *supervisor);
t_supervisor	*parse_input(int ac, char **av);
void			debug_print_supervisor_data(t_supervisor supervisor);
#endif