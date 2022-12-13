/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   threads.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkocob <dkocob@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/13 17:34:31 by dkocob        #+#    #+#                 */
/*   Updated: 2022/12/13 23:35:54 by dkocob        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void *ft_phil_routine(void *val)
{
    struct s_philosopher *philo = (struct s_philosopher *)val;

    while (philo->eat_count != 0)
    {
        if (!ft_eat(philo) || death_set(philo) == 1)
            return (NULL);
        philo->eat_count--;
        if (!ft_sleep(philo) || death_set(philo) == 1)
            return (NULL);
        if (!ft_think(philo) || death_set(philo) == 1)
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
