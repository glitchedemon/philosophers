/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfai <lfai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 14:34:18 by lfai              #+#    #+#             */
/*   Updated: 2023/06/26 15:26:45 by lfai             ###   ########.fr       */
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
	int				n_philo;
	int				time_to_die;
	int				time_to_sleep;
	int				time_to_eat;
	int				eat_or_die;
	int				full_philo;
	t_philo			*philo;
	pthread_mutex_t	check_mutex;
	pthread_mutex_t	*fork;
	pthread_mutex_t print;
	pthread_mutex_t death;
	int				the_end;
}	t_monitor;

typedef struct s_philo
{
	int				id;
	int				eaten_meals;
	int				time_start;
	int				n_philo;
	int				time_to_die;
	int				time_to_sleep;
	int				time_to_eat;
	int				full_philo;
	t_monitor		*monitor; //only to access the_end
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t *print;
	pthread_mutex_t *death;

}	t_philo;



int	main(int argc, char **argv);

#endif
