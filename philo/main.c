/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 20:27:35 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/10/31 20:21:03 by gbuczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	clean(t_table *table)
{
	// clean all the mutexes
	(void)table;
}

int	main(int argc, char **argv)
{
	t_table	table;

	if (!validate_arguments(argc, argv))
	{
		initialize_table(&table, argv);
		begin_philosophers_routine(&table);
		begin_monitoring(&table);
		join_threads(&table);
		free_philosophers(&table);
	}
	return (0);
}
