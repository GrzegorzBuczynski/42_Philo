

#include "philo.h"

#define PHILO_NUM 3

typedef struct s_philo
{
	int				id;
	struct s_table	*table;
	pthread_t		*thread;
	long			last_eat;
	long			last_sleep;

}					t_philosopher;

typedef struct s_table
{
	int				runing;
	pthread_mutex_t	**mutex;
	pthread_mutex_t	*mutex_odd;
	pthread_mutex_t	*mutex_even;
	t_philosopher	**philosopher;
	int				philo_num;
	int				id;
	int				time_to_eat;
	long			time_to_sleep;
}					t_table;

void	precise_usleep(long usec)
{
	long	elapsed;
	long	rem;

	struct timeval start, current;
	gettimeofday(&start, NULL);
	do
	{
		gettimeofday(&current, NULL);
		elapsed = get_elapsed_time_microseconds(start, current);
		rem = usec - elapsed;
		if (rem > 1000)
			usleep(rem / 2);
	} while (elapsed < usec);
}

void	eating(t_philosopher *philosopher)
{
	printf("Philosopher %d is eating\n", philosopher->id);
	precise_usleep(philosopher->table->time_to_eat);
}

void	lock_itself(t_table *table)
{
	if (table->id % 2 == 0)
		pthread_mutex_lock(table->mutex_even);
	else
		pthread_mutex_lock(table->mutex_odd);
}

void	unlock_oposit(t_table *table)
{
	if (table->id % 2 == 0)
		pthread_mutex_unlock(table->mutex_odd);
	else
		pthread_mutex_unlock(table->mutex_even);
}

void	lock_forks(t_table *table)
{
	pthread_mutex_lock(table->mutex[table->id]);
	pthread_mutex_lock(table->mutex[(table->id + 1) % table->philo_num]);
}

void	*thinking(void *arg)
{
	t_table	*table;
	int		i;

	table = (t_table *)arg;
	i = table->id;
	printf("Philosopher %d is thinking\n", i);
	return (NULL);
}

void	*do_philo_stuff(void *arg)
{
	t_table			*table;
	t_philosopher	*philosopher;

	while (table->runing)
		;
	table = (t_table *)arg;
	philosopher = (t_table *)arg->philosopher[table->id];
	eating(philosopher);
	sleeping(philosopher);
	thinking(philosopher);
	return (NULL);
}
/*

	zablokuj 3 mutexy
	myslenie
  if (wezmiesz 2 mutexy )
	zwolnij pozostale mutexy


philo 1 bierz 1 i 2


*/
void	init_table(t_table *table, int philo_num)
{
	table->philo_num = philo_num;
	table->mutex = (pthread_mutex_t **)malloc(sizeof(pthread_mutex_t *) * 2
			* philo_num);
	table->philosopher = (t_philosopher **)malloc(sizeof(t_philosopher *)
			* philo_num);
	table->runing = 0;
}

void	init_mutex(pthread_mutex_t **mutex, int philo_num)
{
	int	i;

	i = 0;
	while (i < 2 * philo_num)
	{
		mutex[i] = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
		i++;
	}
	i = 0;
	while (i < 2 * philo_num)
	{
		printf("Mutex %d is created\n", i);
		pthread_mutex_init(mutex[i], NULL);
		i++;
	}
}

t_philosopher	*init_philosopher(int philo_num)
{
	t_philosopher	*philosopher;
	pthread_t		*thread;

	philosopher = (t_philosopher *)malloc(sizeof(t_philosopher));
	thread = (pthread_t *)malloc(sizeof(pthread_t));
	philosopher->id = philo_num;
	if (pthread_create(thread, NULL, do_philo_stuff, NULL) != 0)
		perror("Nie udało się utworzyć wątku dla filozofa");
	
}

int	main(void)
{
	int		philo_num;
	int		i;
	t_table	table;

	philo_num = PHILO_NUM;
	init_table(&table, philo_num);
	init_mutex(table.mutex, philo_num);
	i = 0;
	while (i < philo_num)
	{
		table.philosopher[i] = init_philosopher(i);
		i++;
	}
	table.runing = 1;
}
