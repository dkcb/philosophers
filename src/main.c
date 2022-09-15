/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkocob <dkocob@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/09 18:51:34 by dkocob        #+#    #+#                 */
/*   Updated: 2022/09/15 21:12:42 by dkocob        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"


void ft_phil_init(struct s_philosopher *phil, pthread_mutex_t *mutex, int name, char **argv)
{
    phil->name = name + 1;
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
    // gettimeofday(&phil->act.t_eat, NULL);
    // gettimeofday(&phil->act.t_sleep, NULL);
    // gettimeofday(&phil->act.t_think, NULL);
}
void    take_fork(struct s_philosopher *philo)
{
    printf("taking fork\n");
    if (philo->arms.left.fork == 0)
    {
        printf("to left hand\n");
        philo->arms.left.fork = 1;
        gettimeofday(&philo->arms.left.take, NULL);
        printf(" %ld s %d ms - Philosopher %d has taken a fork\n", philo->arms.left.take.tv_sec, philo->arms.left.take.tv_usec, philo->name);
    }
    else if(philo->arms.right.fork == 0)
    {
        philo->arms.right.fork = 1;
        printf("to right hand\n");
        gettimeofday(&philo->arms.right.take, NULL);
        printf(" %ld s %d ms - Philosopher %d has taken a fork\n", philo->arms.right.take.tv_sec, philo->arms.right.take.tv_usec, philo->name);
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
        printf("waiting for fork\n");
        take_fork(philo);
    }
    gettimeofday(&philo->act.t_eat.start_at, NULL);
    printf(" %ld s %d ms - philosopher %d is eating\n", philo->act.t_eat.start_at.tv_sec, philo->act.t_eat.start_at.tv_usec, philo->name);
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
    printf("Philosopher[%d] is died:%d | has forks:%d\n", philo->name, philo->act.died, philo->arms.left.fork + philo->arms.right.fork);
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

    if (argc < 3)
        return (write(2, "Wrong arguments!\n", 17));
    data.philo = phil;
    pthread_mutex_init(&mutex, NULL);
    while (i < number_of_philosophers - 1)
    {
        ft_phil_init(&data.philo[i], &mutex, i, argv);
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
    // printf("%d seconds and ", (tp2.tv_sec - tp1.tv_sec));
    // printf("%d milliseconds passed since program started\n", (tp2.tv_usec - tp1.tv_usec) / 1000);
    pthread_mutex_destroy(&mutex);
    return 0;
}



    //forks = philosophers
    
//   timestamp_in_ms X has taken a fork ◦ timestamp_in_ms X is eating
// ◦ timestamp_in_ms X is sleeping
// ◦ timestamp_in_ms X is thinking
// ◦ timestamp_in_ms X died died - should be displayed no more than 10 ms
    // printf("time:%d\n", sec2);