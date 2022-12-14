/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   threads.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkocob <dkocob@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/13 17:34:31 by dkocob        #+#    #+#                 */
/*   Updated: 2022/12/14 20:57:08 by dkocob        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"


void *death_thread(void *val)
{
    struct s_data *data = (struct s_data *)val;
    int i;

    while (!death_check(data))
    {
        i = 0;
        while (i < data->number_of_philosophers - 1)
        {
            if (data->philo_arr[i].time_to_live < time_current_long())
            {
                data->dead++;
                pthread_mutex_lock(&data->mprint);
                if (data->dead == 1)
                    printf ("%5ld %d died\n", time_current_long() - data->time_start_long, i + 1);
                pthread_mutex_unlock(&data->mprint);
            }
            i++;
        }
        pthread_mutex_unlock(&data->mdeath);
        usleep(50);
    }
    return (NULL);
}

void *ft_phil_routine(void *val)
{
    struct s_philosopher *philo = (struct s_philosopher *)val;

    while (philo->eat_count != 0 && !death_check(philo->data))
    {
        ft_eat(philo);
        philo->eat_count--;
        if (death_check(philo->data))
            return (NULL);
        ft_sleep(philo);
        if (death_check(philo->data))
            return (NULL);
        ft_think(philo);
        if (death_check(philo->data))
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
        if (pthread_create(&data->threads[i], NULL, &ft_phil_routine, &data->philo_arr[i]) != 0)
        {
            perror("thread creation fails!\n");
            return (1);
        }
        i++;
    }
    if (pthread_create(&data->threads[201], NULL, &death_thread, data) != 0)
    {
        perror("thread creation fails!\n");
        return (1);
    }
    return (0);
}
