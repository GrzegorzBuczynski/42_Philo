/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 20:27:35 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/10/20 20:27:46 by gbuczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_table	table;

	if (validate_arguments(argc, argv))
		return (0);
	initialize_table(&table, argc, argv);
	if (initialize_philosophers(&table))
		return (0);
	create_threads(&table, &table.monitor_thread);
	join_threads(&table, &table.monitor_thread);
	cleanup(&table);
	return (0);
}
