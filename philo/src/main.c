/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkocob <dkocob@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/09 18:51:34 by dkocob        #+#    #+#                 */
/*   Updated: 2022/12/13 23:11:47 by dkocob        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

long time_current_long(void)
{
    struct timeval current;
    
    gettimeofday(&current, NULL);
    return ((current.tv_sec) * 1000 + (current.tv_usec) / 1000);
}

int time_print_diff(struct s_philosopher *philo, int action)
{
    // if (death_check(philo->data) == 1)
    // {   
    //     return (1);
    // }
    pthread_mutex_lock(&philo->data->mprint);
    printf ("%5ld ", time_current_long() - philo->data->time_start_long);
    if (action == 101)
        printf(" %d has taken a fork\n", philo->index);
    if (action == 102)
        printf(" %d has taken a fork\n", philo->index);
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
    // printf ("PRINT\n");
    return (0);
}


// int ft_check_death(struct s_philosopher *philo)
// {
//     // printf ("cdeath1\n");
//     // if (philo->time_to_live - time_current_long() <= 0 || death_check(philo->data) == 1)
//     if (philo->time_to_live - time_current_long() <= 0)
//     {
//         // printf ("cdeath12\n");
//         return (death_set(philo->data, philo->index));
        
//     }
//     // printf ("cdeath2\n");
//     return (0);
// }

int csleep(int ms, long *ttl)
{
    long end;
    int dead;
    // printf ("sleep\n");

    dead = 0;
    end = time_current_long()  + (long)ms;
    if (ms > ttl[0] - time_current_long())
    {
        // printf ("%d: DEAD ttl0 - cur:%ld\n", philo->index, ttl[0] - time_current_long());
        end = ttl[0];
        dead = 1;
    }
    while (time_current_long() < end)
        usleep(250);
    return (dead);
}

int main (int argc, char **argv) 
{
    struct s_philosopher    phil[201];
    pthread_t               threads[201];
    pthread_mutex_t         mforks[201];
    struct s_data           data;

    data.philo_arr = &phil[0];
    data.threads = &threads[0];
    data.mforks = &mforks[0];
    pthread_mutex_init(&data.mprint, NULL);
    pthread_mutex_init(&data.mdeath, NULL);
    if (init(argc, argv, &data) != 0)
        return (-1);
    init_threads(&data);
    cleaning(&data);
    pthread_mutex_destroy(&data.mprint);
    pthread_mutex_destroy(&data.mdeath);
    return (0);
}
