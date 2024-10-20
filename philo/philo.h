

#ifndef PHILO_H
# define PHILO_H

# include <errno.h>
# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>

# define PHILO_NUM 5

typedef enum e_opcade
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH,
}						t_opcode;

typedef enum e_time_code
{
	SECONDS,
	MILLISECONDS,
	MICROSECONDS,
}						t_time_code;

typedef struct s_table	t_table;
typedef pthread_mutex_t	t_mutex;

typedef struct s_fork
{
	t_mutex				fork;
	int					fork_id;

}						t_fork;

typedef struct s_philo
{
	int					id;
	int					meals;
	bool				full;
	long				last_meal_time;
	pthread_t			thread;
	t_fork				*first_fork;
	t_fork				*second_fork;
	t_table				*table;
	t_mutex				*print_lock;
}						t_philo;

typedef struct s_table
{
	long				num_philos;
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;
	long				meals;
	long				start_time;
	bool				end_simulation;
	bool				all_threads_ready;
	t_fork				*forks;
	t_philo				*philos;
	t_mutex				print_lock;
	t_mutex table_mutex; // avoid races while reading from table
	pthread_t			monitor_thread;
}						t_table;

void					*monitor_rutine(void *arg);
void					*philo_rutine(void *arg);

int						meals_left(t_philo *philo);

long					get_time_delta(long start, long end);
// long					get_timestamp(void);
long					get_time(t_time_code time_code);
void					precise_usleep(long usec);
void					wait_all_threads(t_table *table);

long					ft_atol(const char *str);
int						is_positive_integer(const char *str);
int						validate_arguments(int argc, char **argv);

void					safe_thread_handle(pthread_t *thread,
							void *(*foo)(void *), void *data, t_opcode opcode);
void					safe_mutex_handle(t_mutex *mutex, t_opcode opcode);
void					error_exit(const char *error);
void					*safe_malloc(size_t size);

void					set_bool(t_mutex *mutex, bool *dest, bool value);
bool					get_bool(t_mutex *mutex, bool *value);
long					get_long(t_mutex *mutex, long *value);
void					set_long(t_mutex *mutex, long *dest, long value);
bool					simulation_finished(t_table *table);

#endif