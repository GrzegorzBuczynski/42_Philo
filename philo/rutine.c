/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rutine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 20:07:41 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/10/30 20:08:25 by gbuczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philosophers_routine(void *arguments)
{
	t_philo	*philosophers;

	philosophers = (t_philo *)arguments;
	while (philosophers->tab->philosopher_dead == 0 && philosophers->hungry)
	{
		if (philosopher_is_dead(philosophers))
			return (0);
		if (philosopher_takes_forks(philosophers))
			return (0);
		if (philosopher_is_dead(philosophers))
		{
			pthread_mutex_unlock(philosophers->left_fork);
			pthread_mutex_unlock(philosophers->right_fork);
			return (0);
		}
		philosophers_is_eating(philosophers);
		if (philosopher_is_dead(philosophers))
			return (0);
		philosophers_is_sleeping(philosophers);
		if (philosopher_is_dead(philosophers))
			return (0);
		philosophers_is_thinking(philosophers);
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
		pthread_create(&data->philosophers[i].thread_id,
			NULL, &philosophers_routine, (void *)&data->philosophers[i]);
		i++;
	}
}
