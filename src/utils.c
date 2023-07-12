/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfai <lfai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 12:10:21 by lfai              #+#    #+#             */
/*   Updated: 2023/07/12 17:11:03 by lfai             ###   ########.fr       */
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

unsigned long	get_time(t_philo *ph)
{
	struct timeval	tv;
	unsigned long	t;

	gettimeofday(&tv, NULL);
	t = ((tv.tv_sec - ph->time_start) * 1000 + (tv.tv_usec - ph->utime_start) / 1000);
	return (t);
}

void	accurate_sleep(t_philo *ph, int tm)
{
	int	start;

	start = get_time(ph);
	while (get_time(ph)- start < (unsigned long)tm)
		usleep(50);
}

void	mutex_printer(t_philo *ph, char c)
{
	static int	f;

	pthread_mutex_lock(ph->print);
	if (f == 0)
	{
		if (c == 'f')
			printf("%ld %d grab a fork\n", get_time(ph),\
				ph->id);
		else if (c == 'e')
			printf("%ld %d is eating\n", get_time(ph),\
				ph->id);
		else if (c == 's')
			printf("%ld %d is sleeping\n", get_time(ph),\
				ph->id);
		else if (c == 't')
			printf("%ld %d is thinking\n", get_time(ph),\
				ph->id);
		else if (c == 'd')
		{
			printf("%ld %d is dead\n", get_time(ph),\
				ph->id);
			f = 1;
		}
	}
	pthread_mutex_unlock(ph->print);
}
