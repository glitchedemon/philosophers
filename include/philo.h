/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfai <lfai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 14:34:18 by lfai              #+#    #+#             */
/*   Updated: 2023/07/12 17:09:01 by lfai             ###   ########.fr       */
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

struct	s_philo;

typedef struct s_monitor
{
	struct s_philo 	*philo;
	time_t		time_start;
	suseconds_t		utime_start;
	int		n_philo; //num of philos
	int		full_philo;
	int		meals;
	int		time_to_die;
	int		time_to_sleep;
	int		time_to_eat;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	pthread_mutex_t	death;
	pthread_mutex_t	eat;
	int		the_end; //true when a philo dies, stops the routine
}	t_monitor;

typedef struct s_philo
{
	int		id; //philo's name
	pthread_t	th;
	time_t		time_start;
	suseconds_t		utime_start;
	int		meals; //num of meals eaten
	int		meal_count;
	int		*full_philo;
	int		last_meal; // the time when last meal was eaten
	int		n_philo;
	int		time_to_die;
	int		time_to_sleep;
	int		time_to_eat;
	//int		*full_philos;
	int		*the_end;
	t_monitor	*monitor; //access to monitor struct
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*print;
	pthread_mutex_t	*death;
	pthread_mutex_t	*eat;

}	t_philo;



int	main(int argc, char **argv);
long	ft_atoi(char *str);
void	init_thread(t_monitor *monitor);
int	init_forks(t_monitor *monitor);
void	init_philos(t_monitor *monitor);
t_monitor	*init_monitor(char **argv);
void	mutex_printer(t_philo *ph, char c);
void	accurate_sleep(t_philo *ph, int tm);
unsigned long	get_time(t_philo *ph);
void	*routine(void *ptr);
void	the_death(t_monitor *monitor);
int	check_end(t_philo *ph);
int	check_full_philos(t_philo *ph);
void	clear_monitor(t_monitor *monitor);
void    clear_mutex(t_monitor *monitor);



#endif
