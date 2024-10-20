/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 20:26:07 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/10/20 20:27:29 by gbuczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */




#include "philo.h"

void	initialize_table(t_table *table, int argc, char **argv)
{
	table->num_philos = ft_atol(argv[1]);
	table->time_to_die = ft_atol(argv[2]);
	table->time_to_eat = ft_atol(argv[3]);
	table->time_to_sleep = ft_atol(argv[4]);
	if (argc == 6)
		table->meals = ft_atol(argv[5]);
	else
		table->meals = -1;
	table->simulation_running = 0;
}

static void	assign_forks(t_philo *philo, t_fork *forks, int philo_position)
{
	int	num_philos;

	num_philos = philo->table->num_philos;
	if (philo->id % 2 == 0)
	{
		philo->first_fork = &forks[philo_position];
		philo->second_fork = &forks[(philo_position + 1) % num_philos];
	}
	else
	{
		philo->first_fork = &forks[(philo_position + 1) % num_philos];
		philo->second_fork = &forks[philo_position];
	}
}

static void	philo_init(t_table *table)
{
	int		i;
	t_philo	*philo;

	i = -1;
	while (++i < table->num_philos)
	{
		philo = table->philos + i;
		philo->id = i + 1;
		philo->full = false;
		philo->meals = 0;
		philo->table = table;
		assign_forks(&table->philos[i], table->forks, i);
	}
}

int	init_data(t_table *table)
{
	int	i;

	i = -1;
	table->end_simulation = false;
	table->philos = safe_malloc(sizeof(t_philo) * table->num_philos);
	safe_mutex_handle(&table->table_mutex, INIT);
	table->forks = safe_malloc(sizeof(pthread_mutex_t) * table->num_philos);
	while (++i < table->num_philos)
	{
		safe_mutex_handle(&table->forks[i].fork, INIT);
		table->forks[i].fork_id = i;
	}
	philo_init(table);
}