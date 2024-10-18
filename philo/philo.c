

#include "philo.h"

#define PHILO_NUM 3

typedef struct s_philo
{
	int				id;
	struct s_table	*table;
	pthread_t		thread;
	struct timeval	last_eat;
	long			last_sleep;
	int				meals_left;

}					t_philo;

typedef struct s_table
{
	int				running;
	pthread_mutex_t	check;
	pthread_mutex_t	*fork;
	t_philo			*philo;
	int				philo_num;
	int				id;
	int				time_to_eat;
	long			time_to_sleep;
	long			time_to_die;
}					t_table;

long	get_utime_delta(struct timeval start, struct timeval end)
{
	long	elapsed;

	elapsed = (end.tv_sec - start.tv_sec) * 1000000;
	elapsed += end.tv_usec - start.tv_usec;
	return (elapsed);
}

void	precise_usleep(long usec)
{
	long	elapsed;
	long	rem;

	struct timeval start, current;
	gettimeofday(&start, NULL);
	do
	{
		gettimeofday(&current, NULL);
		elapsed = get_utime_delta(start, current);
		rem = usec - elapsed;
		if (rem > 1000)
			usleep(rem / 2);
	} while (elapsed < usec);
}

void	init_table(t_table *table, int philo_num)
{
	int	i;

	i = 0;
	table->running = 0;
	table->philo_num = philo_num;
	table->philo = (t_philo *)malloc(sizeof(t_philo) * philo_num);
	table->fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* philo_num);
	table->time_to_eat = 1000;
	table->time_to_sleep = 1000;
	pthread_mutex_init(&table->check, NULL);
	while (i < philo_num)
	{
		table->philo[i].id = i;
		table->philo[i].table = table;
		table->philo[i].meals_left = 10;
		pthread_mutex_init(&table->fork[i], NULL);
		i++;
	}
	pthread_mutex_init(&table->check, NULL);
}

int	check_start(t_philo *philo)
{
	pthread_mutex_lock(&(philo->table->check));
	if (philo->table->running && philo->meals_left)
	{
		pthread_mutex_unlock(&philo->table->check);
		return (1);
	}
	pthread_mutex_unlock(&philo->table->check);
	return (0);
}

void	lock_forks(t_philo *philo)
{
	int	id;
	int	philo_num;

	id = philo->id;
	philo_num = philo->table->philo_num;
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->table->fork[id]);
		pthread_mutex_lock(&philo->table->fork[(id + 1) % philo_num]);
	}
	else
	{
		pthread_mutex_lock(&philo->table->fork[(id + 1) % philo_num]);
		pthread_mutex_lock(&philo->table->fork[id]);
	}
}

void	unlock_forks(t_philo *philo)
{
	int	id;
	int	philo_num;

	id = philo->id;
	philo_num = philo->table->philo_num;
	if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(&philo->table->fork[id]);
		pthread_mutex_unlock(&philo->table->fork[(id + 1) % philo_num]);
	}
	else
	{
		pthread_mutex_unlock(&philo->table->fork[(id + 1) % philo_num]);
		pthread_mutex_unlock(&philo->table->fork[id]);
	}
}

void	eating(t_philo *philo)
{
	lock_forks(philo);
	pthread_mutex_lock(&philo->table->check);
	philo->meals_left--;
	gettimeofday(&philo->last_eat, NULL);
	printf("Philosopher %d is eating\n", philo->id);
	pthread_mutex_unlock(&philo->table->check);
	precise_usleep(philo->table->time_to_eat);
	unlock_forks(philo);
}

void	*thinking(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->table->check);
	printf("Philosopher %d is thinking\n", philo->id);
	pthread_mutex_unlock(&philo->table->check);
	precise_usleep(philo->table->time_to_sleep);
	return (NULL);
}

void	*sleeping(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->table->check);
	printf("Philosopher %d is sleeping\n", philo->id);
	pthread_mutex_unlock(&philo->table->check);
	return (NULL);
}

void	*do_philo_stuff(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (check_start(philo))
	{
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	if (philo->meals_left == 0)
	{
		printf("Philosopher %d is full\n", philo->id);
	}
}
void	perror(const char *__s)
{
	dprintf(STDERR_FILENO, "%s: %s\n", "error", __s);
	exit(1);
}

void	*fmonitor(void *arg)
{
	t_table			*table;
	int				i;
	int				philo_num;
	int				running;
	struct timeval	current;

	table = (t_table *)arg;
	philo_num = table->philo_num;
	running = 1;
	while (running)
	{
		i = 0;
		while (i < philo_num)
		{
			pthread_mutex_lock(&table->check);
			gettimeofday(&current, NULL);
			if (get_utime_delta(table->philo[i].last_eat,
					current) > table->time_to_die)
			{
				printf("Philosopher %d died\n", table->philo[i].id);
				table->running = 0;
				pthread_mutex_unlock(&table->check);
				return (NULL);
			}
			if (table->philo[i].meals_left == 0)
				running = 0;
			pthread_mutex_unlock(&table->check);
			i++;
		}
	}
	table->running = 0;
	return (NULL);
}

int	main(void)
{
	int			philo_num;
	int			i;
	t_table		table;
	pthread_t	*thread;
	t_philo		*philo;
	pthread_t	monitor;

	philo_num = PHILO_NUM;
	init_table(&table, philo_num);
	i = 0;
	while (i < table.philo_num)
	{
		thread = &(table.philo[i].thread);
		philo = &(table.philo[i]);
		if (pthread_create(thread, NULL, do_philo_stuff, philo) != 0)
			perror("Nie udało się utworzyć wątku dla filozofa");
		i++;
	}
	if (pthread_create(&monitor, NULL, fmonitor, &table) != 0)
		perror("Nie udało się utworzyć wątku dla filozofa");
	i = 0;
	while (i < table.philo_num)
	{
		pthread_join(table.philo[i].thread, NULL);
		i++;
	}
	pthread_join(monitor, NULL);
}

// void	init_mutex(pthread_mutex_t **mutex, int philo_num)
// {
// 	int	i;

// 	i = 0;
// 	while (i < 2 * philo_num)
// 	{
// 		mutex[i] = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
// 		i++;
// 	}
// 	i = 0;
// 	while (i < 2 * philo_num)
// 	{
// 		printf("Mutex %d is created\n", i);
// 		pthread_mutex_init(mutex[i], NULL);
// 		i++;
// 	}
// }

// t_philo	*init_philosopher(int philo_num)
// {
// 	t_philo		*philo;
// 	pthread_t	*thread;

// 	philo = (t_philo *)malloc(sizeof(t_philo));
// 	thread = (pthread_t *)malloc(sizeof(pthread_t));
// 	philo->id = philo_num;
// 	if (pthread_create(thread, NULL, do_philo_stuff, NULL) != 0)
// 		perror("Nie udało się utworzyć wątku dla filozofa");
// }
