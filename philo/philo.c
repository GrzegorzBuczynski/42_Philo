

#include "philo.h"

#define PHILO_NUM 3

typedef struct philo
{
	int				id;
	int				time_to_eat;
	long			last_eat;

}					t_philosopher;

typedef struct
{
	pthread_mutex_t	**mutex;
	pthread_mutex_t	*mutex_odd;
	pthread_mutex_t	*mutex_even;
	t_philosopher		**philosopher;
	int				philo_num;
	int				id;
}					t_table;

void	eating(t_table *table)
{
	while (get_time - )
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

void	*do_philo_stuff(void *arg)
{
	t_table			*table;
	t_philosopher	*philosopher;

	table = (t_table *)arg;
	philosopher = (t_table *)arg->philosopher[table->id];
	lock_itself(table);
	lock_forks(table);
	eating(table);
	sleeping(table);
	thinking(table);
	unlock_oposit(table);
	return (NULL);
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

void	init_philosopher(t_philosopher **philosopher, int philo_num)
{
	int	i;

	i = 0;
	while (i < philo_num)
	{
		philosopher[i] = (t_philosopher *)malloc(sizeof(t_philosopher));
		philosopher[i]->thread = (pthread_t *)malloc(sizeof(pthread_t));
		philosopher[i]->id = i;
		i++;
	}
}

int	main(void)
{
	int		philo_num;
	int		i;
	t_table	table;

	philo_num = PHILO_NUM;
	init_table(&table, philo_num);
	init_philosopher(table.philosopher, philo_num);
	init_mutex(table.mutex, philo_num);
	i = 0;
	i = 0;
	while (i < philo_num)
	{
		printf("Philosopher %d is thinking\n", i);
		pthread_create(table.philosopher[i]->thread, NULL, eating, &table);
		i++;
	}
	i = 0;
	while (i < philo_num)
	{
		printf("Philosopher %d is dead\n", i);
		// pthread_join(thread[i], NULL);
		i++;
	}
}
