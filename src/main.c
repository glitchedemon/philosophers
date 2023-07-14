/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfai <lfai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 14:35:59 by lfai              #+#    #+#             */
/*   Updated: 2023/07/12 16:49:44 by lfai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	clear_monitor(t_monitor *monitor)
{
	if (monitor->forks)
		free(monitor->forks);
	if (monitor->philo)
		free(monitor->philo);
    free(monitor);
}

void    clear_all(t_monitor *monitor)
{
    int i;

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

int	main(int argc, char **argv)
{
    t_monitor   *monitor;

    if (argc < 5 || argc > 6)
        return (1);
    monitor = init_monitor(argv);
    if(!monitor)
        return (0);
    init_forks(monitor);
    init_philos(monitor);
    init_thread(monitor);
    clear_all(monitor);
}

