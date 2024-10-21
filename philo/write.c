/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ja <ja@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 15:03:30 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/10/21 22:00:10 by ja               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	write_status_debug(t_philo_status status, t_philo *philo,
		long elapsed)
{
	if (((TAKE_FIRST_FORK == status) || (TAKE_SECOND_FORK == status))
		&& !simulation_finished(philo->table))
			printf("%-6ld %d has taken a fork\n", elapsed, philo->id);
	else if (EATING == status && !simulation_finished(philo->table))
		printf("%-6ld %d is eating\n", elapsed, philo->id);
	else if (SLEEPING == status && !simulation_finished(philo->table))
		printf("%-6ld %d is sleeping\n", elapsed, philo->id);
	else if (THINKING == status && !simulation_finished(philo->table))
		printf("%-6ld %d is thinking\n", elapsed, philo->id);
	else if (DEAD == status && !simulation_finished(philo->table))
		printf("%-6ld %d died\n", elapsed, philo->id);
}

void	write_status(t_philo_status status, t_philo *philo, bool debug)
{
	long elapsed;

	if (philo->full)
		return ;
	elapsed = get_time(MILLISECONDS) - philo->table->start_time;
	safe_mutex_handle(&philo->table->write_mutex, LOCK);
	if (debug)
		write_status_debug(status, philo, elapsed);
	if ((TAKE_FIRST_FORK == status) && !simulation_finished(philo->table))
		printf("%-6ld %d has taken the 1 fork %d\n", 
			elapsed, philo->id, philo->first_fork->fork_id);
	else if ((TAKE_SECOND_FORK == status) && !simulation_finished(philo->table))
		printf("%-6ld %d has taken the 2 fork %d\n", 
			elapsed, philo->id, philo->second_fork->fork_id);
	else if (EATING == status && !simulation_finished(philo->table))
		printf("%-6ld %d is eating"
			" %d \n", elapsed, philo->id, philo->meals);
	else if (SLEEPING == status && !simulation_finished(philo->table))
		printf("%-6ld %d is sleeping\n", elapsed, philo->id);
	else if (THINKING == status && !simulation_finished(philo->table))
		printf("%-6ld %d is thinking\n", elapsed, philo->id);
	else if (DEAD == status && !simulation_finished(philo->table))
		printf("%-6ld %d died\n", elapsed, philo->id);
	safe_mutex_handle(&philo->table->write_mutex, UNLOCK);
}