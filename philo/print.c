/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 15:43:17 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/10/20 18:52:38 by gbuczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void print_message(t_philo *philo, const char *message)
{
	pthread_mutex_lock(philo->print_lock);
	printf("%ld Philosopher %d %s\n", get_time_delta(philo->table->start_time, get_timestamp()),
		philo->id, message);
	pthread_mutex_unlock(philo->print_lock);
}