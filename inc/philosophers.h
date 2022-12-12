/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkocob <dkocob@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/09 18:52:30 by dkocob        #+#    #+#                 */
/*   Updated: 2022/12/12 21:05:51 by dkocob        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <errno.h>
# include <sys/wait.h>
# include "libft/libft.h"
# include <sys/time.h>
# include <pthread.h>

#define FORK1 101
#define FORK2 102
#define EATING 10
#define STOPEATING 11
#define SLEAPING 20
#define STOPSLEAPING 21
#define THINKING 3
#define DIED 0
#define F1 philo->index - 1
#define F2 philo->index % philo->data->number_of_philosophers
struct s_philosopher
{
    struct s_data   *data;
    long            time_to_live;
    // struct timeval  time_current;
    struct timeval  last_meal;
    int             index;
    int             eat_count;
};

struct s_data
{
    int                     dead;
    int                     time_to_eat;
    int                     time_to_sleep;
    int                     time_to_die;
    int                     meals_total;
    int                     number_of_philosophers;
    struct s_philosopher    *philo;
    pthread_mutex_t         *mforks;
    pthread_mutex_t         *mdead;
    pthread_mutex_t         *mprint;
    long                    start_time_long;
    struct timeval          time_from_start;
};

#endif

