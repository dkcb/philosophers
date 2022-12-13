/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   threads.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkocob <dkocob@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/13 17:34:31 by dkocob        #+#    #+#                 */
/*   Updated: 2022/12/13 22:24:01 by dkocob        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

int death_check(struct s_data *data)
{
    printf ("DC1\n");
    
    pthread_mutex_lock(&data->mdeath);
    if (data->dead == 1)
        return (1);
    return (0);
    printf ("DC2\n");
    pthread_mutex_unlock(&data->mdeath);
    printf ("DC3\n");

}

int death_set(struct s_data *data, int index)
{
    printf ("DS1\n");
    pthread_mutex_lock(&data->mdeath);
    if (data->dead != 1)
    {
        
        pthread_mutex_lock(&data->mprint);
        printf ("%5ld ", time_current_long() - data->time_start_long);
        printf(" %d died\n", index);
        printf ("DS12\n");
        pthread_mutex_lock(&data->mprint);
    }
    data->dead = 1;
    pthread_mutex_unlock(&data->mdeath);
    printf ("DS2\n");
    return (1);
}

void *ft_phil_routine(void *val)
{
    struct s_philosopher *philo = (struct s_philosopher *)val;

    while (philo->eat_count != 0)
    {
        if (!ft_eat(philo) || ft_check_death(philo) == 1)
            return (NULL);
        philo->eat_count--;
        if (!ft_sleep(philo) || ft_check_death(philo) == 1)
            return (NULL);
        if (!ft_think(philo) || ft_check_death(philo) == 1)
            return (NULL);
    }
    return (NULL);
}

int init_threads(struct s_data *data)
{
    int i;

    i = 0;
    while (i < data->number_of_philosophers)
    {
        usleep (i % 2 * data->time_to_eat);
        if (pthread_create(&data->threads[i], NULL, &ft_phil_routine, &data->philo_arr[i]) != 0)
        {
            perror("thread creation fails!\n");
            return (1);
        }
        i++;
    }
    return (0);
}
