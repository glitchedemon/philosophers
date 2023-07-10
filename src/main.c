/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfai <lfai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 14:35:59 by lfai              #+#    #+#             */
/*   Updated: 2023/07/10 16:19:06 by lfai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	main(int argc, char **argv)
{
    t_monitor   *monitor;

    if (argc < 5 || argc > 6)
        return (1);

}

// init mutex and array of struct
    // pthreadcreate
    // routine (while 1)
    // funzione per la morte tra create e join(ciclo while)
    // pthreadjoin
    // mutexdestroy
    // free mem
    // usleep 10k per pari o dispari nella routine
