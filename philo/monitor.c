/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 15:00:04 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/11/05 17:16:33 by gbuczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_alive(t_philo *philo)
{
	if (get_time() - philo->tab->starting_time > philo->time_to_die)
	{
		philo->tab->philosopher_dead = 1;
		if (philo->hungry)
			printf("%d %d died\n", get_time() - philo->tab->starting_time,
				philo->id);
		return (0);
	}
	else
		return (1);
}

int	check_if_one_is_dead_or_full(t_table *tab)
{
	int	i;

	i = 0;
	while (i < tab->number_of_philosophers)
	{
		if (tab->philosophers[i].meals_eaten == tab->number_of_meals)
			tab->philosophers[i].hungry = 0;
		if (!is_alive(&tab->philosophers[i]))
			return (ERROR);
		i++;
	}
	return (1);
}

void	free_philosophers(t_table *philosophers)
{
	free(philosophers->philosophers);
	free(philosophers->fork_mutex);
}

void	*begin_monitoring(void *arg)
{
	t_table	*table;
	int		i;

	i = 1;
	table = (t_table *)arg;
	while (i)
	{
		pthread_mutex_lock(&table->mutex);
		if (check_if_one_is_dead_or_full(table) == ERROR)
		{
			usleep(100);
			i = 0;
			pthread_mutex_unlock(&table->mutex);
			return (NULL);
		}
		pthread_mutex_unlock(&table->mutex);
		usleep(200);
	}
	return (NULL);
}
