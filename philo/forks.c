/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 15:10:49 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/10/20 16:21:30 by gbuczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// void	lock_forks(t_philo *philo)
// {
// 	int				id;
// 	int				philo_num;
// 	struct timeval	current;

// 	id = philo->id;
// 	philo_num = philo->table->philo_num;
// 	if (philo->id % 2 == 0)
// 	{
// 		pthread_mutex_lock(&philo->table->fork[(id + 1) % philo_num]);
// 		pthread_mutex_lock(&philo->table->check);
// 		gettimeofday(&current, NULL);
// 		printf("%ld Philosopher %d has taken fork %d\n",
// 			(get_utime_delta(philo->table->sim_start_time, current) * 1000000),
// 			id, (id + 1) % philo_num);
// 		pthread_mutex_lock(&philo->table->fork[id]);
// 		printf("%ld Philosopher %d has taken fork %d\n",
// 			(get_utime_delta(philo->table->sim_start_time, current) * 1000000),
// 			id, id);
// 		pthread_mutex_unlock(&philo->table->check);
// 	}
// 	else
// 	{
// 		pthread_mutex_lock(&philo->table->check);
// 		pthread_mutex_lock(&philo->table->fork[id]);
// 		gettimeofday(&current, NULL);
// 		printf("%ld Philosopher %d has taken fork %d\n",
// 			(get_utime_delta(philo->table->sim_start_time, current) * 1000000),
// 			id, id);
// 		pthread_mutex_lock(&philo->table->fork[(id + 1) % philo_num]);
// 		printf("%ld Philosopher %d has taken fork %d\n",
// 			(get_utime_delta(philo->table->sim_start_time, current) * 1000000),
// 			id, (id + 1) % philo_num);
// 		pthread_mutex_unlock(&philo->table->check);
// 	}
// }

// void	unlock_forks(t_philo *philo)
// {
// 	int	id;
// 	int	philo_num;

// 	id = philo->id;
// 	philo_num = philo->table->philo_num;
// 	if (philo->id % 2 == 0)
// 	{
// 		pthread_mutex_unlock(&philo->table->fork[id]);
// 		pthread_mutex_unlock(&philo->table->fork[(id + 1) % philo_num]);
// 	}
// 	else
// 	{
// 		pthread_mutex_unlock(&philo->table->fork[(id + 1) % philo_num]);
// 		pthread_mutex_unlock(&philo->table->fork[id]);
// 	}
// }

long get_value(t_mutex philo, long *value)
{
	if (value < 0)
		return (0);
	return (value);
}

int	meals_left(t_philo *philo)
{
	if (philo->meals > 0)
	{
		return (1);
	}
	return (0);
}