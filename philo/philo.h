

#ifndef PHILO_H
# define PHILO_H

# define TRUE 1
# define SUCCESS 1
# define FALSE 0
# define ERROR 0
# define FAILURE 0

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	int				id;
	int				last_meal;
	int				is_eating;
	int				time_to_die;
	int				time_to_sleep;
	int				time_to_eat;
	int				meals_eaten;
	int				hungry;
	pthread_t		thread_id;
	struct s_table	*tab;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
}					t_philo;

typedef struct s_table
{
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_sleep;
	int				time_to_eat;
	int				number_of_meals;
	int				starting_time;
	int				philosopher_dead;
	pthread_mutex_t	*fork_mutex;
	pthread_mutex_t	mutex;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_philo			*philosophers;
}					t_table;

int					initialize_table(t_table *tab, char **argv);
void				print_limits_error(void);
void				print_right_syntax(void);
void				philosophers_is_eating(t_philo *philosophers);
void				philosophers_is_sleeping(t_philo *philosophers);
void				philosophers_is_thinking(t_philo *philosophers);
void				*philosophers_routine(void *arguments);
void				begin_philosophers_routine(t_table *data);
void				free_philosophers(t_table *philosophers);
void				*begin_monitoring(void *arg);
void				join_threads(t_table *data);
void				print_message(char *str, t_philo *philosopher);
void				ft_sleep(int time, t_philo *philosophers);

long				ft_atoi_long(const char *str);

int					philosopher_is_dead(t_philo *philosophers);
int					philosopher_takes_forks(t_philo *philosophers);
int					ft_atoi(const char *str);
int					init_mutex(t_table *tab);
int					get_time(void);
int					validate_arguments(int argc, char **argv);
long				ft_atol(const char *str);

#endif