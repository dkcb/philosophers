/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkocob <dkocob@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/09 18:51:34 by dkocob        #+#    #+#                 */
/*   Updated: 2022/09/09 20:14:40 by dkocob        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"


//Philosophers with threads and mutexes

// memset, printf, malloc, free, write,
// usleep, gettimeofday, pthread_create,
// pthread_detach, pthread_join, pthread_mutex_init,
// pthread_mutex_destroy, pthread_mutex_lock,
// pthread_mutex_unlock

// Each philosopher should be a thread.
// • There is one fork between each pair of philosophers. Therefore, if there are several philosophers, each philosopher has a fork on their left side and a fork on their right side. If there is only one philosopher, there should be only one fork on the table.
// • To prevent philosophers from duplicating forks, you should protect the forks state with a mutex for each of them.

int main (int argc, char **argv) //number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]

{
    int i = 0;
    int sec = 0;
    int sec2 = 0;
    struct timeval tp1;
    struct timeval tp2;

    gettimeofday(&tp1, NULL);
    usleep(2000);
    gettimeofday(&tp2, NULL);
    //eat - only with 2 forks
    //think
    //sleep


    //forks = philosophers
    
//   timestamp_in_ms X has taken a fork ◦ timestamp_in_ms X is eating
// ◦ timestamp_in_ms X is sleeping
// ◦ timestamp_in_ms X is thinking
// ◦ timestamp_in_ms X died died - should be displayed no more than 10 ms
    // printf("time:%d\n", sec);
    // printf("time:%d\n", sec2);
    // printf("time:%d\n", tp1.tv_sec /365/24/60/60);
    // printf("time:%d\n", tp2.tv_sec /365/24/60/60);
    // printf("time:%d\n", (tp2.tv_sec - tp1.tv_sec) / 1000);

    printf("%d seconds and ", (tp2.tv_sec - tp1.tv_sec));
    printf("%d milliseconds\n", (tp2.tv_usec - tp1.tv_usec) / 1000);
    return 0;
}
