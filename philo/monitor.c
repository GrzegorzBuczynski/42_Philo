/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 15:00:04 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/10/20 15:38:25 by gbuczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor_rutine(void *arg)
{
	return (NULL);
}
// {
// 	t_table			*table;
// 	int				i;
// 	int				philo_num;
// 	int				running;
// 	struct timeval	current;
// 	struct timeval	current2;
// 	long			elapsed;

// 	table = (t_table *)arg;
// 	philo_num = table->philo_num;
// 	running = 1;
// 	while (running && table->running)
// 	{
// 		i = 0;
// 		while (i < philo_num)
// 		{
// 			pthread_mutex_lock(&table->check);
// 			gettimeofday(&current, NULL);
// 			// usleep(1500000);
// 			// gettimeofday(&current2, NULL);
// 			// elapsed = get_utime_delta(current, current2);
// 			// elapsed = get_utime_delta(table->philo[i].last_eat, current);
// 			// elapsed = elapsed / 1000000;
// 			if (get_time_delta(table->philo[i].last_eat, current) > table->time_to_die)
// 			{
// 				printf("Philosopher %d died\n", table->philo[i].id);
// 				table->running = 0;
// 				pthread_mutex_unlock(&table->check);
// 				return (NULL);
// 			}
// 			if (table->philo[i].meals_left == 0)
// 				running = 0;
// 			pthread_mutex_unlock(&table->check);
// 			i++;
// 		}
// 	}
// 	table->running = 0;
// 	return (NULL);
// }