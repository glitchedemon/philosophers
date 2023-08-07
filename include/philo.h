/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfai <lfai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 14:34:18 by lfai              #+#    #+#             */
/*   Updated: 2023/08/07 17:05:41 by lfai             ###   ########.fr       */
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

/*!
 * @brief all data needed for the routine
 * @param n_philo number of philosophers
 * @param full_philo philos that have already eaten
 * @param meals number of meals
 * @param philo pointer to s_philo
 * @param forks mutex for the forks
 * @param print mutex for printing
 * @param death mutex when a philo dies
 * @param eat mutex when eating
 * @param the_end true when a philo dies
 */
typedef struct s_monitor
{
	struct s_philo		*philo;
	time_t				time_start;
	suseconds_t			utime_start;
	int					n_philo;
	int					full_philo;
	int					meals;
	int					time_to_die;
	int					time_to_sleep;
	int					time_to_eat;
	int					the_end;
	pthread_mutex_t		*forks;
	pthread_mutex_t		print;
	pthread_mutex_t		death;
	pthread_mutex_t		eat;
}	t_monitor;

/*!
 * @brief philosophers' kit
 * @param id philo's name
 * @param th thread
 * @param meal_count counter for the meals left
 * @param last_meal the moment when last meal was eaten
 * @param monitor pointer to s_monitor
 * @param r_fork mutex for the right fork
 * @param l_fork mutex for the left fork
 */
typedef struct s_philo
{
	int					id;
	pthread_t			th;
	time_t				time_start;
	suseconds_t			utime_start;
	int					meals;
	int					meal_count;
	int					*full_philo;
	int					last_meal;
	int					n_philo;
	int					time_to_die;
	int					time_to_sleep;
	int					time_to_eat;
	int					*the_end;
	t_monitor			*monitor;
	pthread_mutex_t		*r_fork;
	pthread_mutex_t		*l_fork;
	pthread_mutex_t		*print;
	pthread_mutex_t		*death;
	pthread_mutex_t		*eat;
}	t_philo;

int				main(int argc, char **argv);
long			ft_atoi(char *str);
void			init_thread(t_monitor *monitor);
int				init_forks(t_monitor *monitor);
void			init_philos(t_monitor *monitor);
t_monitor		*init_monitor(char **argv);
unsigned long	ft_get_time(t_philo *ph);
void			*check_monitor(char **argv, t_monitor *monitor);
void			mutex_printer(t_philo *ph, char c);
void			accurate_sleep(t_philo *ph, int tm);
void			*routine(void *ptr);
void			routine_helper(t_philo *ph);
void			the_death(t_monitor *monitor);
void			death_2(t_monitor *monitor, int *i);
int				check_end(t_philo *ph);
int				check_full_philos(t_philo *ph);
void			clear_monitor(t_monitor *monitor);
void			clear_all(t_monitor *monitor);
int				ft_isdigit(int c);
int				ft_checkarg(char **argv);

#endif
