/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   actions.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkocob <dkocob@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/13 18:16:00 by dkocob        #+#    #+#                 */
/*   Updated: 2022/12/13 22:21:52 by dkocob        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

int    ft_eat(struct s_philosopher *philo)
{
    pthread_mutex_lock(&philo->data->mforks[F1]);
    if (ft_check_death(philo))
    {
        pthread_mutex_unlock(&philo->data->mforks[F1]);
        return (-1);
    }
    time_print_diff(philo, FORK1); //???
    pthread_mutex_lock(&philo->data->mforks[F2]);
    if (ft_check_death(philo))
    {
        pthread_mutex_unlock(&philo->data->mforks[F1]);
        pthread_mutex_unlock(&philo->data->mforks[F2]);
        return (-1);
    }
    time_print_diff(philo, FORK2);
    time_print_diff(philo, EATING);
    philo->time_to_live = time_current_long() + philo->data->time_to_die;
    if (csleep(philo->data->time_to_eat, &philo->time_to_live))
        return (death_set(philo->data, philo->index));
    pthread_mutex_unlock(&philo->data->mforks[F1]);
    pthread_mutex_unlock(&philo->data->mforks[F2]);
    return (1);
}

int ft_sleep(struct s_philosopher *philo)
{
    time_print_diff(philo, SLEAPING);
    if (csleep(philo->data->time_to_sleep, &philo->time_to_live))
        return (death_set(philo->data, philo->index));
    return (1);
}

int    ft_think(struct s_philosopher *philo)
{
    if (ft_check_death(philo))
        return (-1);
    time_print_diff(philo, 3);
    return (1);
}