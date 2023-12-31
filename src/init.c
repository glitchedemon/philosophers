/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfai <lfai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 15:35:32 by lfai              #+#    #+#             */
/*   Updated: 2023/08/07 17:03:44 by lfai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/*!
 * @brief init s_monitor struct
 * @param monitor pointer to s_monitor struct
 * @param argv arguments given when starting the program
 * @param argc num of arguments given when starting the program
 */
t_monitor	*init_monitor(char **argv)
{
	t_monitor		*monitor;
	struct timeval	tv;

	monitor = malloc(sizeof(t_monitor));
	gettimeofday(&tv, NULL);
	monitor->time_start = tv.tv_sec;
	monitor->utime_start = tv.tv_usec;
	monitor->n_philo = ft_atoi(argv[1]);
	monitor->time_to_die = ft_atoi(argv[2]);
	monitor->time_to_eat = ft_atoi(argv[3]);
	monitor->time_to_sleep = ft_atoi(argv[4]);
	check_monitor(argv, monitor);
	if (monitor->n_philo <= 0 || monitor->time_to_die <= 0 || \
		monitor->time_to_eat <= 0 || monitor->time_to_sleep <= 0 \
		|| monitor->meals <= 0)
		return (NULL);
	monitor->the_end = 0;
	monitor->full_philo = 0;
	monitor->philo = malloc(sizeof(t_philo) * monitor->n_philo);
	pthread_mutex_init(&monitor->print, NULL);
	pthread_mutex_init(&monitor->death, NULL);
	pthread_mutex_init(&monitor->eat, NULL);
	monitor->forks = malloc(sizeof(pthread_mutex_t) * monitor->n_philo);
	return (monitor);
}

void	*check_monitor(char **argv, t_monitor *monitor)
{
	if (argv[5] != NULL)
		monitor->meals = ft_atoi(argv[5]);
	else
		monitor->meals = __INT_MAX__;
	return (0);
}

/*!
 * @brief init s_philo struct
 * @param monitor pointer to s_monitor
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
		monitor->philo[i].meal_count = 0;
		monitor->philo[i].time_to_die = monitor->time_to_die;
		monitor->philo[i].time_to_eat = monitor->time_to_eat;
		monitor->philo[i].time_to_sleep = monitor->time_to_sleep;
		monitor->philo[i].time_start = monitor->time_start;
		monitor->philo[i].utime_start = monitor->utime_start;
		monitor->philo[i].last_meal = ft_get_time(&monitor->philo[i]);
		monitor->philo[i].the_end = &monitor->the_end;
		monitor->philo[i].death = &monitor->death;
		monitor->philo[i].print = &monitor->print;
		monitor->philo[i].the_end = &monitor->the_end;
		monitor->philo[i].eat = &monitor->eat;
		monitor->philo[i].full_philo = &monitor->full_philo;
		i++;
	}
}

/*!
 * @brief ft used to init the forks, it ensures that each philosopher
 * can access the appropriate forks
 * @param monitor
 * @return
 */
int	init_forks(t_monitor *monitor)
{
	int	i;

	i = 0;
	while (i < monitor->n_philo)
	{
		pthread_mutex_init(&monitor->forks[i], NULL);
		i++;
	}
	i = 0;
	monitor->philo[monitor->n_philo - 1].l_fork = &monitor->forks[0];
	monitor->philo[monitor->n_philo - 1].r_fork = \
		&monitor->forks[monitor->n_philo - 1];
	i = 0;
	while (i < monitor->n_philo - 1)
	{
		monitor->philo[i].l_fork = &monitor->forks[i];
		monitor->philo[i].r_fork = &monitor->forks[i + 1];
		i++;
	}
	return (0);
}

/*!
 * @brief ft used to init the thread in order to start the routine.
 * Death function is in between thread create and join so it won't
 * bother during the routine
 * @param monitor
 */
void	init_thread(t_monitor *monitor)
{
	int	i;

	i = 0;
	while (i < monitor->n_philo)
	{
		pthread_create(&monitor->philo[i].th, NULL, &routine, \
			&monitor->philo[i]);
		i++;
	}
	the_death(monitor);
	i = 0;
	while (i < monitor->n_philo)
	{
		pthread_join(monitor->philo[i].th, NULL);
		i++;
	}
}
