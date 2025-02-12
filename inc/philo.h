/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 13:19:11 by jnenczak          #+#    #+#             */
/*   Updated: 2025/02/12 16:14:32 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <string.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>
# include <limits.h>
# define RESET_COLOR "\033[0m"
# define GREEN_COLOR "\033[32m"
# define YELLOW_COLOR "\033[33m"
# define CYAN_COLOR "\033[36m"
# define RED_COLOR "\033[31m"
# define BLUE_COLOR "\033[34m"
# define THINKING_EMOJI "🤔"
# define EATING_EMOJI "🍝"
# define FORK_EMOJI "🍴"
# define SLEEPING_EMOJI "😴"
# define DIED_EMOJI "💀"
# define PREETY_PRINT TRUE

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
	long			meals_eaten;
	long			index;
	long			last_sleep;
	long			last_thinking;
	long			last_meal;
	t_activity		activity;
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
	t_bool			*dinner_over;
	pthread_mutex_t	edit_lock;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*dinner_over_lock;
	pthread_mutex_t	*dead_lock;
}	t_philo;

typedef struct s_supervisor
{
	unsigned long	sim_start;
	long			number_of_philo;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			number_of_meals;
	t_philo			**philos;
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
long			input_atoi_long(const char *str);
void			init_supervisor_numbers(t_supervisor *super, char **av);
t_philo			**init_philos(t_supervisor *super);
t_fork			**init_forks(t_supervisor *super);
void			free_until(void **elem, int i);
struct timeval	get_sim_runtime(struct timeval start);
void			assign_forks(t_supervisor *super);
void			action_eat(t_philo *philo);
void			action_think(t_philo *philo);
void			action_sleep(t_philo *philo);
void			action_put_down_forks(t_philo *philo);
void			action_pick_up_forks(t_philo *philo);
unsigned long	get_sim_runtime_milliseconds(struct timeval simulation_start);
unsigned long	get_time_since_last_meal(t_philo *philo);
int				ft_usleep(unsigned long milliseconds);
unsigned long	ft_get_current_time(void);
unsigned long	get_runtime_in_ms(t_philo *philo);
int				input_check_empty(const char *str);
long			input_strtol(const char *str, char **endptr);
int				input_check_valid_number(const char *str);
long			input_atoi_long(const char *str);
void			init_supervisor(t_supervisor *super);
t_bool			check_dinner_over(t_philo *philo);
t_bool			check_error(t_philo *philo);
void			*supervisor_routine(t_supervisor *super);
#endif