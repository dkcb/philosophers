/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkocob <dkocob@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/09 18:52:30 by dkocob        #+#    #+#                 */
/*   Updated: 2022/09/14 21:47:02 by dkocob        ########   odam.nl         */
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
    int taken;
};

struct s_time
{
    struct timeval since;
    struct timeval last;
    int taken;
    int begin;
    int end;
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

    struct s_fork forks;
    struct s_arms arms;
    struct s_activity act;
    struct s_time dead;
    pthread_mutex_t *mutex;
    
};

struct s_data
{

    struct s_philosopher *philo;
    
};


#endif

