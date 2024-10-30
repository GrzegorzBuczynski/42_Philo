/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 15:00:04 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/10/30 20:18:08 by gbuczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_last_meal(t_philo *philo)
{
	if (get_time() - philo->tab->starting_time > philo->time_to_die)
	{
		philo->tab->philosopher_dead = 1;
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
		if (tab->philosophers[i].hungry != 0)
			if (check_last_meal(&tab->philosophers[i]) == ERROR)
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
	t_table	*data;

	data = (t_table *)arg;
	while (1)
	{
		pthread_mutex_lock(&data->mutex);
		if (check_if_one_is_dead_or_full(data) == ERROR)
		{
			usleep(100);
			return (pthread_mutex_unlock(&data->mutex), NULL);
		}
		pthread_mutex_unlock(&data->mutex);
		usleep(200);
	}
}
