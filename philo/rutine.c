/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rutine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 20:07:41 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/11/05 17:15:49 by gbuczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_hungry(t_philo *philo)
{
	pthread_mutex_lock(&philo->tab->mutex);
	if (philo->hungry)
	{
		pthread_mutex_unlock(&philo->tab->mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->tab->mutex);
	return (0);
}

int	one_philo(t_philo *philo)
{
	if (philo->tab->number_of_philosophers == 1)
	{
		pthread_mutex_lock(&philo->tab->mutex);
		printf("0 1 has taken a fork\n");
		pthread_mutex_unlock(&philo->tab->mutex);
		usleep(philo->tab->time_to_die * 1000);
		return (1);
	}
	return (0);
}

void	*philosophers_routine(void *arguments)
{
	t_philo	*philo;

	philo = (t_philo *)arguments;
	if (one_philo(philo))
		return (NULL);
	while (philo->tab->philosopher_dead == 0 && is_hungry(philo))
	{
		if (philosopher_takes_forks(philo))
			return (0);
		if (philosopher_is_dead(philo))
		{
			pthread_mutex_unlock(philo->left_fork);
			pthread_mutex_unlock(philo->right_fork);
			return (0);
		}
		philosophers_is_eating(philo);
		philosophers_is_sleeping(philo);
		philosophers_is_thinking(philo);
	}
	return (0);
}

void	join_threads(t_table *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		pthread_join(data->philosophers[i].thread_id, NULL);
		i++;
	}
}

void	begin_philosophers_routine(t_table *data)
{
	int	i;

	i = 0;
	data->starting_time = get_time();
	while (i < data->number_of_philosophers)
	{
		pthread_create(&data->philosophers[i].thread_id, NULL,
			&philosophers_routine, (void *)&data->philosophers[i]);
		i++;
	}
}
