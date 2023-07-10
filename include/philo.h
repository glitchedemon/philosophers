/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfai <lfai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 14:34:18 by lfai              #+#    #+#             */
/*   Updated: 2023/07/10 16:13:44 by lfai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_monitor
{
	pthread_t	*th;
	time_t		time_start;
	suseconds_t	utime_start; //microseconds
	int		n_philo; //num of philos
	int		meals;
	unsigned long	time_start; //time when the simulation starts
	int		time_to_die;
	int		time_to_sleep;
	int		time_to_eat;
	int		full_philos; // true when all philos have eaten, stops the routine
	t_philo 	*philo;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	pthread_mutex_t	death;
	int		the_end; //true when a philo dies, stops the routine
}	t_monitor;

typedef struct s_philo
{
	int		id; //philo's name
	time_t		time_start;
	suseconds_t	utime_start;
	int		meals; //num of meals eaten
	int		last_meal; // the time when last meal was eaten
	int		n_philo;
	int		time_to_die;
	int		time_to_sleep;
	int		time_to_eat;
	int		*full_philos;
	int		*the_end;
	t_monitor	*monitor; //access to monitor struct
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*print;
	pthread_mutex_t	*death;

}	t_philo;



int	main(int argc, char **argv);
int	ft_atoi(const char *str);
void	init_thread(t_monitor *monitor);
int	init_forks(t_monitor *monitor);
void	init_philos(t_monitor *monitor);
void	init_monitor(t_monitor *monitor, char **argv, int argc);
void	mutex_printer(t_philo *ph, char c);
void	accurate_sleep(t_philo *ph, int tm);
int	actual_time(time_t start, suseconds_t ustart);


#endif
