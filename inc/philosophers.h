/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkocob <dkocob@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/09 18:52:30 by dkocob        #+#    #+#                 */
/*   Updated: 2022/10/10 17:05:04 by dkocob        ########   odam.nl         */
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

struct s_fork
{
    int fork;
    struct timeval take;
    struct timeval put;
};

struct s_time
{
    struct timeval start_at;
    struct timeval stop_at;
    // int prev_begin;
    // int prev_end;
};

struct s_arms
{
    struct s_fork left;
    struct s_fork right;
};

struct s_activity
{
    int taken_a_fork;
    int is_eating;
    int is_sleeping;
    int is_thinking;
    int died;
    struct s_time t_eat;
    struct s_time t_think;
    struct s_time t_sleep;
};
struct s_philosopher
{
    int index;
    int time_to_eat;
    int time_to_sleep;
    int time_to_die;
    int meals_total;
    struct s_fork forks;
    struct s_arms arms;
    struct s_activity act;
    struct s_time dead;
    struct timeval *time_from_start;
    struct timeval time_current;
    pthread_mutex_t *mutex;
};

struct s_data
{
    struct s_philosopher *philo;
    struct s_fork *fork;
    struct timeval time_from_start;
};


#endif

