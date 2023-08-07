/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfai <lfai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 16:46:58 by lfai              #+#    #+#             */
/*   Updated: 2023/08/07 17:23:59 by lfai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/*!
 * @brief ft used to check if all philos have eaten
 * @param ph pointer to s_philo
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

/*!
 * @brief checks the value of the end, return 1 if a philo died
 * @param ph pointer to s_philo
 * @return
 */
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

/*!
 * @brief ft used to print each mutex status at specific times in ms
 * @param ph pointer to s_philo
 * @param c status
 * @param f flag
 */
void	mutex_printer(t_philo *ph, char c)
{
	static int	f = 0;

	pthread_mutex_lock(ph->print);
	if (f == 0)
	{
		if (c == 'f')
			printf("%ld %d has taken a fork\n", ft_get_time(ph), \
				ph->id);
		else if (c == 'e')
			printf("%ld %d is eating\n", ft_get_time(ph), \
				ph->id);
		else if (c == 's')
			printf("%ld %d is sleeping\n", ft_get_time(ph), \
				ph->id);
		else if (c == 't')
			printf("%ld %d is thinking\n", ft_get_time(ph), \
				ph->id);
		else if (c == 'd')
		{
			printf("%ld %d died\n", ft_get_time(ph), \
				ph->id);
			f = 1;
		}
	}
	pthread_mutex_unlock(ph->print);
}
