/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ja <ja@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 20:27:35 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/10/21 21:50:34 by ja               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void clean()
{
	//clean all the mutexes
}

int	main(int argc, char **argv)
{
	t_table	table;

	if (validate_arguments(argc, argv))
		return (0);
	initialize_table(&table, argc, argv);
	init_data(&table);
	dinner_start(&table);
	clean(&table); //when simulation is finished  | philo died
	return (0);
}
