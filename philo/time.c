/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ja <ja@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 15:11:43 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/10/21 20:53:31 by ja               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	wait_all_threads(t_table *table)
{
	while (!get_bool(&table->table_mutex, &table->all_threads_ready))
		;
}

long	get_time_delta(long start, long end)
{
	long	elapsed;

	elapsed = end - start;
	return (elapsed);
}

long	get_timestamp(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((long)(time.tv_sec * 1000) + (time.tv_usec / 1000));
}

long get_time(t_time_code time_code)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL))
		error_exit("gettimeofday failed");
	if (time_code == SECONDS)
		return (time.tv_sec + time.tv_usec / 1e6);
	else if (time_code == MILLISECONDS)
		return (time.tv_sec * 1e3 + time.tv_usec / 1e3);
	else if (time_code == MICROSECONDS)
		return (time.tv_sec * 1e6 + time.tv_usec);
	else
		error_exit("Invalid time code");
	return (1337);
}

