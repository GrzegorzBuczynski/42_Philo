

#include "philo.h"

#define PHILO_NUM 3

typedef struct
{
	int				id;
	pthread_t		*thread;
}					Philosopher;

typedef struct
{
	pthread_mutex_t	**mutex;
	Philosopher		**philosopher;
	int				philo_num;
	int				id;
}					t_table;

void	*eating(void *arg)
{
	t_table	*table;
	int		i;

	table = (t_table *)arg;
	i = table->id;
	pthread_mutex_lock(table->mutex[i]);
	pthread_mutex_lock(table->mutex[i + 1]);
	printf("Philosopher %d is eating\n", i);
	sleep(1);
	pthread_mutex_unlock(table->mutex[i]);
	pthread_mutex_unlock(table->mutex[i + 1]);
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
	table->philosopher = (Philosopher **)malloc(sizeof(Philosopher *)
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

void	init_philosopher(Philosopher **philosopher, int philo_num)
{
	int	i;

	i = 0;
	while (i < philo_num)
	{
		philosopher[i] = (Philosopher *)malloc(sizeof(Philosopher));
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
