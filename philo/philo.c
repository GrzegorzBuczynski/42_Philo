/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 20:55:20 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/10/31 20:52:43 by gbuczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philosopher_takes_forks(t_philo *philosophers)
{
	if (philosophers->id % 2 == 0)
		pthread_mutex_lock(philosophers->right_fork);
	else
		pthread_mutex_lock(philosophers->left_fork);
	if (!philosopher_is_dead(philosophers))
		print_message("has taken a fork", philosophers);
	if (philosophers->id % 2 == 0)
	{
		if (pthread_mutex_lock(philosophers->left_fork) != 0)
			return (pthread_mutex_unlock(philosophers->right_fork), 1);
		if (!philosopher_is_dead(philosophers))
			print_message("has taken a fork", philosophers);
	}
	else
	{
		if (pthread_mutex_lock(philosophers->right_fork) != 0)
			return (pthread_mutex_unlock(philosophers->left_fork), 1);
		if (!philosopher_is_dead(philosophers))
			print_message("has taken a fork", philosophers);
	}
	return (0);
}

void	philosophers_is_eating(t_philo *philosophers)
{
	print_message("is eating", philosophers);
	pthread_mutex_lock(&philosophers->tab->mutex);
	philosophers->last_meal = get_time() - philosophers->tab->starting_time;
	philosophers->time_to_die = philosophers->last_meal
		+ philosophers->tab->time_to_die;
	pthread_mutex_unlock(&philosophers->tab->mutex);
	ft_sleep(philosophers->tab->time_to_eat, philosophers);
	pthread_mutex_lock(&philosophers->tab->mutex);
	if (philosophers->meals_eaten != -1)
		philosophers->meals_eaten++;
	pthread_mutex_unlock(&philosophers->tab->mutex);
	pthread_mutex_unlock(philosophers->left_fork);
	pthread_mutex_unlock(philosophers->right_fork);
}

void	philosophers_is_sleeping(t_philo *philosophers)
{
	print_message("is sleeping", philosophers);
	ft_sleep(philosophers->tab->time_to_sleep, philosophers);
}

void	philosophers_is_thinking(t_philo *philosophers)
{
	print_message("is thinking", philosophers);
}

int	philosopher_is_dead(t_philo *philosophers)
{
	pthread_mutex_lock(&philosophers->tab->mutex);
	if (philosophers->tab->philosopher_dead == 1)
	{
		pthread_mutex_unlock(&philosophers->tab->mutex);
		return (1);
	}
	pthread_mutex_unlock(&philosophers->tab->mutex);
	return (0);
}
