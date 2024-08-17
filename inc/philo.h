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
	FALSE,
	TRUE
}	t_bool;

typedef enum s_activity
{
	EATING,
	SLEEPING,
	THINKING,
	DIED,
	FORK
}	t_activity;

typedef struct s_fork
{
	pthread_mutex_t	lock;
	int				index;
}	t_fork;

typedef struct s_philo
{
	long			meals_eaten; // The number of meals the philosopher has consumed so far
	long			index; // Starting with 1
	long			last_sleep; // TS Since the beginning of last sleeping session
	long			last_thinking; // TS Since the beginning of last thinking session
	long			last_meal; // TS Since the beginning of last eating session
	t_activity		activity; // Current philosopher activity
	pthread_t		thread;
	t_fork			*left;
	t_fork			*right;
	long			*number_of_philo;
	long			*time_to_die;
	long			*time_to_eat;
	long			*time_to_sleep;
	long			*number_of_meals_to_eat;
	unsigned long	*simulation_start; 
	t_bool			is_full;
	t_bool			*error;
	pthread_mutex_t	edit_lock;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*dinner_over_lock;
	pthread_mutex_t	*dead_lock;
}	t_philo;

typedef struct s_supervisor
{
	unsigned long	sim_start; // TS of sim start
	long			number_of_philo; // Total number of philosophers
	long			time_to_die; // The max time between meals (or the beginning of the simulation and the first meal)
	long			time_to_eat; // The time it takes the philosopher to eat
	long			time_to_sleep; // The time it takes the philosopher to sleep
	long			number_of_meals; // The number of meals each philosopher has to eat before the end of simulation (-1 means INF)
	t_philo			**philos; // Pointer to an array of philosophers
	t_fork			**forks;
	pthread_t		thread;
	t_bool			error;
	t_bool			dinner_over;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	dinner_over_lock;
	pthread_mutex_t	dead_lock;
}	t_supervisor;

const char		*get_activity_description(t_activity activity);
void			print_philo_state(t_philo *philo);
void			print_error(const char *err);
void			free_resources(t_supervisor *supervisor);
t_supervisor	*parse_input(int ac, char **av);
void			debug_print_supervisor_data(t_supervisor supervisor);
long			custom_atoi_long(const char *str);
void			init_supervisor_numbers(t_supervisor *super, char **av);
t_philo			**init_philos(t_supervisor *super);
t_fork			**init_forks(t_supervisor *super);
void			free_until(void **elem, int i);
struct timeval	get_sim_runtime(struct timeval start);
void			assign_forks_to_philos(t_supervisor *super);
void			eat(t_philo *philo);
void			think(t_philo *philo);
void			philo_sleep(t_philo *philo);
void			put_down_forks(t_philo *philo);
void			pick_up_forks(t_philo *philo);
unsigned long	get_sim_runtime_milliseconds(struct timeval simulation_start);
unsigned long	get_time_since_last_meal(t_philo *philo);
int				ft_usleep(unsigned long milliseconds);
unsigned long	ft_get_current_time(void);
unsigned long	get_runtime_in_ms(t_philo *philo);
#endif