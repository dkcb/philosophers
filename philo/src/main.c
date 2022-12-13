/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkocob <dkocob@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/09 18:51:34 by dkocob        #+#    #+#                 */
/*   Updated: 2022/12/13 18:25:46 by dkocob        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

long time_vs_current(struct timeval *t2)
{
    struct timeval current;
    
    gettimeofday(&current, NULL);
    return ((current.tv_sec - t2->tv_sec) * 1000 + (current.tv_usec - t2->tv_usec) / 1000);
}

int time_print_diff(struct s_philosopher *philo, int action)
{
    pthread_mutex_lock(&philo->data->mprint);
    if (philo->data->dead == 1)
    {
        pthread_mutex_unlock(&philo->data->mprint);
        return (1);
    }
    printf("%ld", time_vs_current(&philo->data->time_from_start));
    if (action == 0)
    {   
        if (philo->data->dead == 0)
        {
            printf(" === philo %d, did not eat %ldms of %dms\n", philo->index, time_vs_current(&philo->last_meal), philo->data->time_to_die);
            printf(" %d died\n", philo->index);
        }
        philo->data->dead = 1;
        pthread_mutex_unlock(&philo->data->mprint);
        return (1);
    }
    if (action == 101)
        printf(" %d has taken a fork1\n", philo->index);
    if (action == 102)
        printf(" %d has taken a fork2\n", philo->index);
    if (action == 10)
        printf(" %d is eating\n", philo->index);
    if (action == 11)
        printf(" %d stoped eating --\n", philo->index);
    if (action == 20)
        printf(" %d is sleeping\n", philo->index);
    if (action == 21)
        printf(" %d stoppped sleeping\n", philo->index);
    if (action == 3)
        printf(" %d is thinking\n", philo->index);
    pthread_mutex_unlock(&philo->data->mprint);
    return (0);
}


int ft_check_death(struct s_philosopher *philo)
{
    // if (philo->data) > philo->data->time_to_die)
    //     return (time_print_diff(philo, DIED));
    if (time_vs_current(&philo->last_meal) > philo->data->time_to_die)
        return (time_print_diff(philo, DIED));
    return (0);
}

int csleep(int ms, int *ttl)
{
    long end;
    struct timeval cur;

    gettimeofday(&cur, NULL);
    // printf("ttl1: %d\n", (int)(*ttl - cur.tv_sec * 1000 - cur.tv_usec / 1000));
    // else
    // {
    end = cur.tv_sec * 1000 + cur.tv_usec / 1000  + ms;
    //     *ttl = *ttl - ms;
    // }
    while (cur.tv_sec * 1000 + cur.tv_usec / 1000 <= end)
    {
        if (!(int)(*ttl - cur.tv_sec * 1000 - cur.tv_usec / 1000))
        {
            // end = cur.tv_sec * 1000 + cur.tv_usec / 1000  + *ttl;
            return (1);
        }
        usleep(250);
        gettimeofday(&cur, NULL);
    }
    // printf("ttl2: %d", *ttl - cur);
    return (0);
}

int main (int argc, char **argv) 
{
    struct s_philosopher    phil[201];
    pthread_t               threads[201];
    pthread_mutex_t         mforks[201];
    struct s_data           data;

    data.philo = &phil[0];
    data.threads = &threads[0];
    data.mforks = &mforks[0];
    pthread_mutex_init(&data.mprint, NULL);
    if (init(argc, argv, &data) != 0)
        return (-1);
    init_threads(&data);
    cleaning(&data);
    pthread_mutex_destroy(&data.mprint);
    return (0);
}
