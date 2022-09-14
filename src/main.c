/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkocob <dkocob@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/09 18:51:34 by dkocob        #+#    #+#                 */
/*   Updated: 2022/09/14 19:45:07 by dkocob        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void ft_phil_init(struct s_philosopher *phil)
{
    phil->arms.left.taken = 1;
    phil->arms.right.taken = 0;
    phil->act.died = 0;
    phil->act.is_eating = 0;
    phil->act.is_sleeping = 0;
    phil->act.is_thinking = 0;
    gettimeofday(&phil->act.t_eat, NULL);
    gettimeofday(&phil->act.t_sleep, NULL);
    gettimeofday(&phil->act.t_think, NULL);
}

void* ft_print_yo(void *val)
{
    // pthread_mutex_lock(&mutex);
    printf("Yo!\n");
    // pthread_mutex_unlock(&mutex);
}

void *ft_phil_state(void *val)
{
    struct s_philosopher *phil = (struct s_philosopher *)val;
    printf("is died:%d | ", phil->act.died);
    printf("%d fork in left ", phil->arms.left.taken);
    printf("and %d in the right arm \n", phil->arms.right.taken);

}

//Philosophers with threads and mutexes

// memset, printf, malloc, free, write,
// usleep, gettimeofday, pthread_create,
// pthread_detach, pthread_join, pthread_mutex_init,
// pthread_mutex_destroy, pthread_mutex_lock,
// pthread_mutex_unlock

// Each philosopher should be a thread.
// • There is one fork between each pair of philosophers. Therefore, if there are several philosophers, each philosopher has a fork on their left side and a fork on their right side. If there is only one philosopher, there should be only one fork on the table.
// • To prevent philosophers from duplicating forks, you should protect the forks state with a mutex for each of them.

// int main (int argc, char **argv) //number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
int main () //number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]

{
    int i = 0;
    // int sec = 0;
    // int sec2 = 0;
    int number_of_philosophers = 5;
    pthread_t t1;
    pthread_mutex_t mutex;
    struct timeval tp1;
    struct timeval tp2;
    struct s_philosopher phil[number_of_philosophers];

    pthread_mutex_init(&mutex, NULL);
    gettimeofday(&tp1, NULL);
    // phil = malloc(sizeof(phil) * 3);
    // phil[3] = NULL;
    while (i < number_of_philosophers)
    {
        ft_phil_init(&phil[i]);
        i++;
    }
    i = 0;
    while (i < number_of_philosophers)
    {

        printf("Philosopher[%d] ", i + 1);
        if (pthread_create(&t1, NULL, &ft_phil_state, &phil[i]) != 0)
        {
            perror("thread creation fails!\n");
            return (1);
        }
        if (pthread_join(t1, NULL) != 0)
        {
            perror("thread join fails!\n");
            return (2);
        }
        printf("\n");
        // ft_phil_state(&phil[i]);
        i++;
    }
    // while (i < number_of_philosophers)
    // {

    //     printf("Philosopher[%d]", i + 1);
    //     if (pthread_create(&t1, NULL, &ft_print_yo, NULL) != 0)
    //     {
    //         perror("thread creation fails!\n");
    //         return (1);
    //     }
    //     if (pthread_join(t1, NULL) != 0)
    //     {
    //         perror("thread join fails!\n");
    //         return (2);
    //     }
    //     ft_phil_state(&phil[i]);
    //     i++;
    // }
    // usleep(2000);
    //eat - only with 2 forks
    //think
    //sleep


    //forks = philosophers
    
//   timestamp_in_ms X has taken a fork ◦ timestamp_in_ms X is eating
// ◦ timestamp_in_ms X is sleeping
// ◦ timestamp_in_ms X is thinking
// ◦ timestamp_in_ms X died died - should be displayed no more than 10 ms
    // printf("time:%d\n", sec2);

    gettimeofday(&tp2, NULL);
    printf("%d seconds and ", (tp2.tv_sec - tp1.tv_sec));
    printf("%d milliseconds passed since program started\n", (tp2.tv_usec - tp1.tv_usec) / 1000);
    pthread_mutex_destroy(&mutex);
    return 0;
}
