/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfai <lfai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 14:35:59 by lfai              #+#    #+#             */
/*   Updated: 2023/08/07 17:26:13 by lfai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

int	ft_checkarg(char **argv)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (argv[i] != NULL)
	{
		while (argv[i][j] != '\0')
		{
			if (ft_isdigit(argv[i][j]) == 0)
				return (0);
			j++;
		}
		j = 0;
		i++;
	}
	return (1);
}

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
 * @brief The program begins by checking the number of command-line
 * arguments (argc).
 * It expects either 5 or 6 arguments(philosopher count, time to die,
 * time to eat, time to sleep, and optionally the number of meals)
 * @param argc
 * @param argv
 * @return
 */
int	main(int argc, char **argv)
{
	t_monitor	*monitor;

	if (argc < 5 || argc > 6)
		return (0);
	else
	{
		if (ft_checkarg(argv) == 0)
			return (0);
		monitor = init_monitor(argv);
		if (!monitor)
			return (0);
		init_forks(monitor);
		init_philos(monitor);
		init_thread(monitor);
	}
	clear_all(monitor);
}
