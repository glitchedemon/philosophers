/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfai <lfai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 15:35:32 by lfai              #+#    #+#             */
/*   Updated: 2023/07/10 15:39:10 by lfai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/*!
 * @brief
 * @param monitor
 * @param argv
 * @param argc
 */
void	init_monitor(t_monitor *monitor, char **argv, int argc)
{
	int	i;
	struct timeval	tv;

	i = -1;
	gettimeofday(&tv, NULL);
	monitor->time_start = tv.tv_sec;
	monitor->utime_start = tv.tv_usec;
	monitor->n_philo = ft_atoi(argv[1]);
	monitor->time_to_die = ft_atoi(argv[2]);
	monitor->time_to_eat = ft_atoi(argv[3]);
	monitor->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		monitor->meals = ft_atoi(argv[5]);
	else
		monitor->meals = -1;
	monitor->full_philos = monitor->n_philo;
	monitor->the_end = 0;
	monitor->philo = malloc(sizeof(t_philo) * monitor->n_philo);
	monitor->th = malloc(sizeof(pthread_t) * monitor->n_philo);
	pthread_mutex_init(&monitor->print, NULL);
	pthread_mutex_init(&monitor->death, NULL);
	monitor->forks = malloc(sizeof(pthread_mutex_t) * monitor->n_philo);
	init_forks(monitor);
	return (0);
}

/*!
 * @brief
 * @param monitor
 * @return
 */
void	init_philos(t_monitor *monitor)
{
	int	i;

	i = 0;
	while (i < monitor->n_philo)
	{
		monitor->philo[i].id = i + 1;
		monitor->philo[i].n_philo = monitor->n_philo;
		monitor->philo[i].meals = monitor->meals;
		monitor->philo[i].last_meal = actual_time(monitor->time_start, monitor->utime_start);
		monitor->philo[i].time_to_die = monitor->time_to_die;
		monitor->philo[i].time_to_eat = monitor->time_to_eat;
		monitor->philo[i].time_to_sleep = monitor->time_to_sleep;
		monitor->philo[i].the_end = monitor->the_end;
		monitor->philo[i].time_start = monitor->time_start;
		monitor->philo[i].utime_start = monitor->utime_start;
		monitor->philo[i].death = &monitor->death;
		monitor->philo[i].print = &monitor->print;
		monitor->philo[i].full_philos = &monitor->full_philos;
		monitor->philo[i].the_end = &monitor->the_end;
		init_forks(&monitor->philo[i]);
		i++;
	}
}

/*!
 * @brief
 * @param monitor
 * @return
 */
int	init_forks(t_monitor *monitor)
{
	int	i;

	i = -1;
	while (++i < monitor->n_philo)
		pthread_mutex_init(&monitor->forks[i], NULL);
	i = 0;
	monitor->philo[0].l_fork = &monitor->forks[0];
	monitor->philo[0].r_fork = &monitor->forks[monitor->n_philo - 1];
	i = 1;
	while (i < monitor->n_philo)
	{
		monitor->philo[i].l_fork = &monitor->forks[i];
		monitor->philo[i].r_fork = &monitor->forks[i - 1];
	}
	return (0);
}

/*!
 * @brief
 * @param monitor
 */
void	init_thread(t_monitor *monitor)
{
	int	i;

	i = 0;
	while (i < monitor->n_philo)
	{
		pthread_create(&monitor->th[i], NULL,/*&routine*/ &monitor->philo[i]);
		i++;
	}
	//death_ft
	i = 0;
	while (i < monitor->n_philo)
	{
		pthread_join(monitor->th[i], NULL);
		i++;
	}
}
