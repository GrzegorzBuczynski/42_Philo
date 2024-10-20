/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 20:07:41 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/10/20 21:02:43 by gbuczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*dinner_simulation(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	wait_all_threads(philo->table);
	return (NULL);
}

void	dinner_start(t_table *table)
{
	int i;

	i = -1;
	if (0 == table->meals)
		return ;
	else if (1 == table->meals)
		; // TODO
	else
	{
		while (++i < table->num_philos)
			safe_thread_handle(&table->philos[i].thread, dinner_simulation,
				&table->philos[i], CREATE);
	}
	table->start_time = get_time(MILLISECONDS);
	set_bool(&table->table_mutex, &table->all_threads_ready, true);
	i = -1;
	while (++i < table->num_philos)
		safe_thread_handle(&table->philos[i].thread, NULL, NULL, JOIN);
}