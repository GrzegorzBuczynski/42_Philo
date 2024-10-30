/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 20:26:07 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/10/30 20:09:19 by gbuczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_philos(t_table *tab)
{
	int	i;

	i = 0;
	tab->philosophers = malloc(sizeof(t_philo) * tab->number_of_philosophers);
	if (!tab->philosophers)
		return (FAILURE);
	while (i < tab->number_of_philosophers)
	{
		tab->philosophers[i].id = i + 1;
		tab->philosophers[i].left_fork = &tab->fork_mutex[i];
		tab->philosophers[i].right_fork = &tab->fork_mutex[(i + 1)
			% tab->number_of_philosophers];
		tab->philosophers[i].tab = tab;
		tab->philosophers[i].time_to_die = tab->time_to_die;
		tab->philosophers[i].time_to_eat = tab->time_to_eat;
		tab->philosophers[i].time_to_sleep = tab->time_to_sleep;
		tab->philosophers[i].last_meal = 0;
		tab->philosophers[i].is_eating = 0;
		tab->philosophers[i].meals_eaten = 0;
		tab->philosophers[i].hungry = 1;
		i++;
	}
	return (SUCCESS);
}

int	init_mutex(t_table *tab)
{
	int	i;

	i = -1;
	tab->fork_mutex = malloc(sizeof(pthread_mutex_t)
			* tab->number_of_philosophers);
	if (!tab->fork_mutex)
		return (FAILURE);
	while (++i < tab->number_of_philosophers)
		pthread_mutex_init(&tab->fork_mutex[i], NULL);
	pthread_mutex_init(&tab->mutex, NULL);
	return (SUCCESS);
}

void	unlock_philosophers_mutex(t_table *philosophers)
{
	pthread_mutex_unlock(philosophers->left_fork);
	pthread_mutex_unlock(philosophers->right_fork);
}

int	initialize_table(t_table *tab, char **argv)
{
	tab->number_of_philosophers = ft_atoi(argv[1]);
	tab->time_to_die = ft_atoi(argv[2]);
	tab->time_to_eat = ft_atoi(argv[3]);
	tab->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		tab->number_of_meals = ft_atoi(argv[5]);
	else
		tab->number_of_meals = -1;
	tab->philosopher_dead = 0;
	if (init_mutex(tab) == FAILURE)
		return (FAILURE);
	if (init_philos(tab) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}
