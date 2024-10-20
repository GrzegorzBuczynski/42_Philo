/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_rutine.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 15:08:20 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/10/20 16:21:30 by gbuczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eating(t_philo *philo)
{
	// lock_forks(philo);
	// pthread_mutex_lock(&philo->table->check);
	// philo->meals_left--;
	// pthread_mutex_lock(&philo->table->check);
	// gettimeofday(&philo->last_eat, NULL);
	// pthread_mutex_unlock(&philo->table->check);
	// printf("Philosopher %d is eating\n", philo->id);
	// pthread_mutex_unlock(&philo->table->check);
	// precise_usleep(philo->table->time_to_eat);
	// printf("Philosopher %d has finished eating\n", philo->id);
	// unlock_forks(philo);
}

void	thinking(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	print_message(philo, "is thinking");
}

void	sleeping(void *arg)
{
	t_philo	*philo;
	long	time_to_sleep;

	philo = (t_philo *)arg;
	print_message(philo, "is sleeping");
	time_to_sleep = get_time_delta(philo->table->start_time, get_timestamp());
	precise_usleep(time_to_sleep);
}

void	*philo_rutine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	wait_for_start(philo->table);
	while (meals_left(philo))
	{
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	// if (philo->meals == 0)
	// {
	// 	printf("Philosopher %d is full\n", philo->id);
	// }
}