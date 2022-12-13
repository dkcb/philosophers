/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   death.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkocob <dkocob@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/13 23:19:23 by dkocob        #+#    #+#                 */
/*   Updated: 2022/12/13 23:36:53 by dkocob        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

int death_set(struct s_philosopher *philo)
{
    // printf ("DS1\n");
    pthread_mutex_lock(&philo->data->mdeath);
    if (philo->data->dead == 1)
    {
        pthread_mutex_unlock(&philo->data->mdeath);
        return (1);
    }
    if (philo->data->dead != 1 && philo->time_to_live - time_current_long() <= 0)
    {
        pthread_mutex_lock(&philo->data->mprint);
        printf ("%5ld ", time_current_long() - philo->data->time_start_long);
        printf(" %d died\n", philo->index);
        // printf ("DS12\n");
        pthread_mutex_unlock(&philo->data->mprint);
        philo->data->dead = 1;
        pthread_mutex_unlock(&philo->data->mdeath);
        return (1);
    }
    pthread_mutex_unlock(&philo->data->mdeath);
    // printf ("DS2\n");
    return (0);
}
