/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfai <lfai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 14:35:59 by lfai              #+#    #+#             */
/*   Updated: 2023/07/19 15:55:52 by lfai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/*!
 * @brief ft to free everything allocated
 * @param monitor
 */
void	clear_monitor(t_monitor *monitor)
{
	if (monitor->forks)
		free(monitor->forks);
	if (monitor->philo)
		free(monitor->philo);
	free(monitor);
}

/*!
 * @brief ft to clear it all
 * @param monitor
 */
void	clear_all(t_monitor *monitor)
{
	int	i;

	i = 0;
	while (i < monitor->n_philo)
	{
		pthread_mutex_destroy(&monitor->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&monitor->eat);
	pthread_mutex_destroy(&monitor->death);
	pthread_mutex_destroy(&monitor->print);
	clear_monitor(monitor);
}

/*!
 * @brief
 * @param argc
 * @param argv
 * @return
 */
int	main(int argc, char **argv)
{
	t_monitor	*monitor;

	if (argc < 5 || argc > 6)
		return (1);
	monitor = init_monitor(argv);
	if (!monitor)
		return (0);
	init_forks(monitor);
	init_philos(monitor);
	init_thread(monitor);
	clear_all(monitor);
}

