/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfai <lfai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 12:10:21 by lfai              #+#    #+#             */
/*   Updated: 2023/07/10 16:03:21 by lfai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ft_atoi(const char *str)
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
	return ((int)(res * sign));
}

int	actual_time(time_t start, suseconds_t ustart)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec - start) * 1000 + (tv.tv_usec - ustart) / 1000);
}

void	accurate_sleep(t_philo *ph, int tm)
{
	int	start;

	start = actual_time(ph->time_start, ph->utime_start);
	while (actual_time(ph->time_start, ph->utime_start)- start < time)
		usleep(50);
}

void	mutex_printer(t_philo *ph, char c)
{
	static int	f;

	pthread_mutex_lock(ph->print);
	if (f == 0)
	{
		if (c == 'f')
			printf("%d %d grab a fork\n", actual_time(ph->time_start, ph->utime_start),\
				ph->id);
		else if (c == 'e')
			printf("%d %d is eating\n", actual_time(ph->time_start, ph->utime_start),\
				ph->id);
		else if (c == 's')
			printf("%d %d is sleeping\n", actual_time(ph->time_start, ph->utime_start),\
				ph->id);
		else if (c == 't')
			printf("%d %d is thinking\n", actual_time(ph->time_start, ph->utime_start),\
				ph->id);
		else if (c == 'd')
		{
			printf("%d %d is dead\n", actual_time(ph->time_start, ph->utime_start),\
				ph->id);
			f = 1;
		}
	}
	pthread_mutex_unlock(ph->print);
}
