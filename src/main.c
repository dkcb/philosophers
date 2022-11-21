/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkocob <dkocob@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/09 18:51:34 by dkocob        #+#    #+#                 */
/*   Updated: 2022/11/21 16:16:48 by dkocob        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"


void time_print_diff(struct timeval *time_from_start, struct timeval *time_current)
{
    printf("%ld%02dms ", time_current->tv_sec - time_from_start->tv_sec, time_current->tv_usec/1000);
}

void ft_phil_init(struct s_philosopher *phil, struct s_data *data, int index)
{
    gettimeofday(&data->time_from_start, NULL);
    gettimeofday(&phil->last_meal, NULL);
    phil->index = index + 1;
    phil->eat_count = 0;
    phil->data->dead = 0;
    phil->data = data;
}

int    ft_check_death(struct s_philosopher *philo)
{

    gettimeofday(&philo->time_current, NULL);
    time_print_diff(&philo->data->time_from_start, &philo->time_current);
    // if ((philo->time_current->tv_sec - philo->data.time_from_start->tv_sec) * 1000 + time_current->tv_usec >)
    printf(" philo %d not eat for %ld ms, of max %d ms --- \n", philo->index, (philo->time_current.tv_sec - philo->last_meal.tv_sec) * 1000 + (philo->time_current.tv_usec - philo->last_meal.tv_usec) / 1000, philo->data->time_to_die);
    if ((philo->time_current.tv_sec - philo->last_meal.tv_sec) * 1000 + (philo->time_current.tv_usec - philo->last_meal.tv_usec) / 1000 > philo->data->time_to_die)
    {
        // printf(" philo %d not eat for %ld ms, of max %d ms ---", philo->index, ((philo->last_meal.tv_sec - philo->data->time_from_start.tv_sec) * 1000 + (philo->last_meal.tv_usec - philo->data->time_from_start.tv_usec)) / 1000, philo->data->time_to_die * 10);
        printf(" philo %d is dead\n \n \n", philo->index);
        philo->data->dead = 1;
    }
    return (philo->data->dead);
}

void    ft_eat(struct s_philosopher *philo)
{
    pthread_mutex_lock(&philo->data->mforks[philo->index - 1]);
    // gettimeofday(&philo->time_current, NULL);
    if (ft_check_death(philo))
    {
        return ;
    }
    printf(" philo %d is eating\n", philo->index);
    usleep(philo->data->time_to_eat * 1000);
    gettimeofday(&philo->last_meal, NULL);
    pthread_mutex_unlock(&philo->data->mforks[philo->index - 1]);
}

void    ft_sleep(struct s_philosopher *philo)
{
    gettimeofday(&philo->time_current, NULL);
    time_print_diff(&philo->data->time_from_start, &philo->time_current);
    printf(" Philo %d is sleeping \n", philo->index);
    usleep(philo->data->time_to_sleep * 1000);
}

void    ft_think(struct s_philosopher *philo)
{
    gettimeofday(&philo->time_current, NULL);
    time_print_diff(&philo->data->time_from_start, &philo->time_current);
    printf(" Philo %d is thinking \n", philo->index);
}

void *ft_phil_routine(void *val)
{
    struct s_philosopher *philo = (struct s_philosopher *)val;

    while (philo->data->dead == 0 && philo->eat_count < philo->data->meals_total)
    {
        ft_eat(philo);
        philo->eat_count++;
        ft_sleep(philo);
        ft_think(philo);
        // ft_check_death(philo);
    }
    return (NULL);
}

int main (int argc, char **argv) //number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
{
    // struct s_philosopher    phil[number_of_philosophers];
    // pthread_t               threads[number_of_philosophers];
    // pthread_mutex_t         mforks[number_of_philosophers];
    // int                     number_of_philosophers = 201;
    int                     number_of_philosophers = ft_atoi(argv[1]);
    struct s_philosopher    phil[number_of_philosophers];
    pthread_t               threads[number_of_philosophers];
    pthread_mutex_t         mforks[number_of_philosophers];
    pthread_mutex_t         mprint;
    pthread_mutex_t         mdeath;
    struct s_data           data;
    int                     i = 1;
    int                     j = 0;

    // printf ("i:%d \n", number_of_philosophers);
    if (argc < 3 || argc > 6)
        return (write(2, "Wrong arguments!\n", 17));
    while (argv[i])
    {
        while(argv[i][j] != '\0')
        {
            if (argv[i][j] >= '0' && argv[i][j] <= '9')
                j++;
            else 
                return (write(2, "Wrong input!\n", 13));
        }
        j = 0;
        i++;
    }
    gettimeofday(&data.time_from_start, NULL);
    data.time_to_die = ft_atoi(argv[2]);
    data.time_to_eat = ft_atoi(argv[3]);
    data.time_to_sleep = ft_atoi(argv[4]);
    data.meals_total = ft_atoi(argv[5]);
    data.mforks = &mforks[0];
    pthread_mutex_init(&mdeath, NULL);
    pthread_mutex_init(&mprint, NULL);
    i = 0;
    while (i < number_of_philosophers)
    {
        ft_phil_init(&phil[i], &data, i);
        pthread_mutex_init(&mforks[i], NULL);
        i++;
    }
    i = 0;
    while (i < number_of_philosophers)
    {
        if (pthread_create(&threads[i], NULL, &ft_phil_routine, &phil[i]) != 0)
        {
            perror("thread creation fails!\n");
            return (1);
        }
        i++;
    }
    i = 0;
    while (i < number_of_philosophers)
    {
        if (pthread_join(threads[i++], NULL))
        {
            perror("thread join fails!\n");
            return (2);
        }
        i++;
    }
    pthread_mutex_destroy(&mforks[0]);
    pthread_mutex_destroy(&mprint);
    pthread_mutex_destroy(&mdeath);
    return 0;
}

// void    ft_check_death(struct s_philosopher *philo)
// {
//     gettimeofday(&philo->time_current, NULL);
//     if (philo->time_current.tv_sec + philo->time_current.tv_sec / 1000 - philo->act.t_eat.stop_at.tv_sec - philo->act.t_eat.stop_at.tv_usec / 1000 >= philo->data->time_to_die)
//     {
//         time_print_diff(&philo->data->time_from_start, &philo->time_current);
//         printf(" Philo %d died ", philo->index);
//         philo->dead = 1;
//     }
// }
// printf("\n-- Philosopher[%d] is died:%d | has forks:%d --\n\n", philo->index, philo->act.died, philo->arms.left.fork + philo->arms.right.fork);
// void    take_fork(struct s_philosopher *philo)
// {
//     if (philo->arms.left.fork == 0)
//     {
//         gettimeofday(&philo->arms.left.take, NULL);
//         time_print_diff(&philo->data->time_from_start, &philo->arms.left.take);
//         printf(" Philo %d taking fork ", philo->index);
//         printf("to left hand\n");
//         philo->arms.left.fork = 1;
//     }
//     else if(philo->arms.right.fork == 0)
//     {
//         gettimeofday(&philo->arms.right.take, NULL);
//         time_print_diff(&philo->data->time_from_start, &philo->arms.right.take);
//         printf(" Philo %d taking fork ", philo->index);
//         printf("to right hand\n");
//         philo->arms.right.fork = 1;
//     }
//     // pthread_mutex_lock(philo->mutex);
// }
// void    put_forks(struct s_philosopher *philo)
// {
//     philo->arms.left.fork = 0;
//     philo->arms.right.fork = 0;
//     // pthread_mutex_unlock(philo->mutex);
// }

// {
//     gettimeofday(&philo->time_current, NULL);
//     time_print_diff(&philo->data->time_from_start, &philo->time_current);
//     printf(" Philo %d is waiting for fork\n", philo->index);
//     take_fork(philo);
// }
// gettimeofday(&philo->act.t_eat.start_at, NULL);
// time_print_diff(&philo->data->time_from_start, &philo->act.t_eat.start_at);
// printf(" philo %d is start eating\n", philo->index);
// sleep(philo->data->time_to_eat);
// put_forks(philo);
// gettimeofday(&philo->act.t_eat.stop_at, NULL);
// time_print_diff(&philo->data->time_from_start, &philo->act.t_eat.stop_at);
// printf(" philo %d stop eating\n", philo->index);

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