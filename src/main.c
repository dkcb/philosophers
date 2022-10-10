/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkocob <dkocob@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/09 18:51:34 by dkocob        #+#    #+#                 */
/*   Updated: 2022/10/10 17:11:38 by dkocob        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"


int time_print_diff(struct timeval *time_from_start, struct timeval *time_current)
{
    printf("%02ld:%02d ", time_current->tv_sec - time_from_start->tv_sec, (time_current->tv_usec - time_from_start->tv_usec)/1000);
    return (0);
}

void ft_phil_init(struct s_philosopher *phil, pthread_mutex_t *mutex, int index, char **argv, struct timeval *time_from_start)
{
    phil->index = index + 1;
    phil->time_from_start = time_from_start;
    phil->time_to_die = ft_atoi(argv[3]);
    phil->time_to_eat = ft_atoi(argv[4]);
    phil->time_to_sleep = ft_atoi(argv[5]);
    phil->meals_total = ft_atoi(argv[6]);
    phil->mutex = mutex;
    phil->arms.left.fork = 1;
    phil->arms.right.fork = 0;
    phil->act.died = 0;
    phil->act.is_eating = 0;
    phil->act.is_sleeping = 0;
    phil->act.is_thinking = 0;
}

void    take_fork(struct s_philosopher *philo)
{
    if (philo->arms.left.fork == 0)
    {
        gettimeofday(&philo->arms.left.take, NULL);
        time_print_diff(philo->time_from_start, &philo->arms.left.take);
        printf(" Philo %d taking fork ", philo->index);
        printf("to left hand\n");
        philo->arms.left.fork = 1;
        gettimeofday(&philo->arms.left.take, NULL);
        time_print_diff(philo->time_from_start, &philo->arms.left.take);
        printf(" Philo %d taking a fork\n", philo->index);
    }
    else if(philo->arms.right.fork == 0)
    {
        gettimeofday(&philo->arms.right.take, NULL);
        time_print_diff(philo->time_from_start, &philo->arms.right.take);
        printf(" Philo %d taking fork ", philo->index);
        printf("to right hand\n");
        philo->arms.right.fork = 1;
    }
    // pthread_mutex_lock(philo->mutex);
}
void    put_forks(struct s_philosopher *philo)
{
    philo->arms.left.fork = 0;
    philo->arms.right.fork = 0;
    // pthread_mutex_unlock(philo->mutex);
}

void    ft_eat(struct s_philosopher *philo)
{
    while(philo->act.is_eating == 0 && (philo->arms.left.fork == 0 || philo->arms.right.fork == 0))
    {
        gettimeofday(&philo->time_current, NULL);
        time_print_diff(philo->time_from_start, &philo->time_current);
        printf(" Philo %d is waiting for fork\n", philo->index);
        take_fork(philo);
    }
    gettimeofday(&philo->act.t_eat.start_at, NULL);
    time_print_diff(philo->time_from_start, &philo->act.t_eat.start_at);
    printf(" philo %d is eating\n", philo->index);
    usleep(philo->time_to_eat);
    put_forks(philo);
    gettimeofday(&philo->act.t_eat.stop_at, NULL);
}

void    ft_sleep(struct s_philosopher *philo)
{
    if (!philo->act.is_sleeping)
    {
        
    }
}

void    ft_think(struct s_philosopher *philo)
{
    if (!philo->act.is_sleeping)
    {
        
    }
}

void    ft_routine(struct s_philosopher *philo)
{
    if (!philo->act.is_eating)
    {
        
    }
    else if (!philo->act.is_sleeping)
    {

    }
    else if (!philo->act.is_thinking)
    {
        
    }
}

// void ft_print_yo(void *val)
// {
//     // pthread_mutex_lock(&mutex);
//     printf("Yo!\n");
//     // pthread_mutex_unlock(&mutex);
// }

// void *ft_phil_state(void *val)
void *ft_phil_routine(void *val)
{
    struct s_philosopher *philo = (struct s_philosopher *)val;

    ft_eat(philo);
    printf("-- Philosopher[%d] is died:%d | has forks:%d --\n\n", philo->index, philo->act.died, philo->arms.left.fork + philo->arms.right.fork);
    return (0);
}
// void *ft_phil_state(void *val, void *mutex)
// {
//     struct s_philosopher *phil = (struct s_philosopher *)val;
//     pthread_mutex_lock(&mutex);
//     printf("is died:%d | ", phil->act.died);
//     printf("%d fork in left ", phil->arms.left.taken);
//     printf("and %d in the right arm \n", phil->arms.right.taken);
//     pthread_mutex_unlock(&mutex);
// }

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
    int                     number_of_philosophers = ft_atoi(argv[2]);
    struct s_philosopher    phil[number_of_philosophers];
    pthread_t               threads[number_of_philosophers];
    pthread_mutex_t         mutex;
    struct s_data           data;
    int                     i = 0;

    gettimeofday(&data.time_from_start, NULL);
    if (argc < 3)
        return (write(2, "Wrong arguments!\n", 17));
    data.philo = phil;
    pthread_mutex_init(&mutex, NULL);
    while (i < number_of_philosophers - 1)
    {
        ft_phil_init(&data.philo[i], &mutex, i, argv, &data.time_from_start);
        i++;
    }
    i = 0;
    while (i < number_of_philosophers - 1)
    {

        if (pthread_create(&threads[i], NULL, &ft_phil_routine, &phil[i]) != 0)
        {
            perror("thread creation fails!\n");
            return (1);
        }
        if (pthread_join(threads[i], NULL) != 0)
        {
            perror("thread join fails!\n");
            return (2);
        }
        i++;
    }
    // eat - only with 2 forks
    // think
    // sleep
    pthread_mutex_destroy(&mutex);
    return 0;
}
