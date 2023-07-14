/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfai <lfai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 15:27:29 by lfai              #+#    #+#             */
/*   Updated: 2023/07/12 17:12:26 by lfai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	check_end(t_philo *ph)
{
	pthread_mutex_lock(ph->death);
	if (*ph->the_end == 1)
	{
		pthread_mutex_unlock(ph->death);
		return (1);
	}
	pthread_mutex_unlock(ph->death);
	return (0);
}

void	the_death(t_monitor *monitor)
{
	int	i;

	i = 0;
	while (1)
	{
		pthread_mutex_lock(&monitor->eat);
		if (monitor->full_philo == monitor->n_philo)
		{
			pthread_mutex_unlock(&monitor->eat);
			return ;
		}
		if (get_time(&monitor->philo[i]) - (unsigned long)monitor->philo[i].last_meal > (unsigned long)monitor->philo[i].time_to_die)
		{
			pthread_mutex_unlock(&monitor->eat);
			pthread_mutex_lock(&monitor->death);
			monitor->the_end = 1;
			pthread_mutex_unlock(&monitor->death);
			mutex_printer(&monitor->philo[i], 'd');
			return ;
		}
		pthread_mutex_unlock(&monitor->eat);
		i++;
		if (i == monitor->n_philo)
			i = 0;
	}
}

/*!
 * @brief
 * @param ph
 * @return
 */
int	check_full_philos(t_philo *ph)
{
		pthread_mutex_lock(ph->eat);
		if (ph->meals == ph->meal_count)
		{
			*ph->full_philo += 1;
			pthread_mutex_unlock(ph->eat);
			return (1);
		}
		pthread_mutex_unlock(ph->eat);
		return (0);
}

void	*routine(void *ptr)
{
	t_philo	*ph;

	ph = (t_philo *)ptr;
	if (ph->id % 2 == 0)
		usleep(10000);
	while (check_end(ph) == 0)
	{
		pthread_mutex_lock(ph->l_fork);
		mutex_printer(ph, 'f');
		pthread_mutex_lock(ph->r_fork);
		mutex_printer(ph, 'f');
		mutex_printer(ph, 'e');
		pthread_mutex_lock(ph->eat);
		ph->last_meal = get_time(ph);
		ph->meal_count++;
		pthread_mutex_unlock(ph->eat);
		pthread_mutex_unlock(ph->r_fork);
		pthread_mutex_unlock(ph->l_fork);
		accurate_sleep(ph, ph->time_to_eat);
		if (check_full_philos(ph) == 1)
			break ;
		mutex_printer(ph, 's');
		accurate_sleep(ph, ph->time_to_sleep);
		mutex_printer(ph, 't');
	}
	return (NULL);
}

