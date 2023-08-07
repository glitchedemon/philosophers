/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfai <lfai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 12:10:21 by lfai              #+#    #+#             */
/*   Updated: 2023/08/07 17:07:38 by lfai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

long	ft_atoi(char *str)
{
	long			res;
	long			sign;
	unsigned int	i;

	res = 0;
	i = 0;
	sign = 1;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || str[i] == '\r'
		|| str[i] == '\v' || str[i] == '\f')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + str[i] - '0';
		i++;
	}
	return ((long)(res * sign));
}

/*!
 * @brief ft used to check the present time in ms
 * @param ph
 * @return
 */
unsigned long	ft_get_time(t_philo *ph)
{
	struct timeval	tv;
	unsigned long	t;

	gettimeofday(&tv, NULL);
	t = ((tv.tv_sec - ph->time_start) * 1000 + \
		(tv.tv_usec - ph->utime_start) / 1000);
	return (t);
}

/*!
 * @brief ft used to make a philo sleep for a specific time in ms
 * @param ph pointer to s_philo
 * @param tm time
 */
void	accurate_sleep(t_philo *ph, int tm)
{
	int	start;

	start = ft_get_time(ph);
	while (ft_get_time(ph)- start < (unsigned long)tm)
		usleep(50);
}
