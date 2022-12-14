/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   actions.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkocob <dkocob@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/13 18:16:00 by dkocob        #+#    #+#                 */
/*   Updated: 2022/12/14 20:12:11 by dkocob        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

int    ft_eat(struct s_philosopher *philo)
{
    usleep ((philo->index + 1) % 2 * 200);
    pthread_mutex_lock(&philo->data->mforks[F1]);
    if (death_check(philo->data))
    {
        pthread_mutex_unlock(&philo->data->mforks[F1]);
        return (-1);
    }
    time_print_diff(philo, FORK1);
    pthread_mutex_lock(&philo->data->mforks[F2]);
    if (death_check(philo->data))
    {
        pthread_mutex_unlock(&philo->data->mforks[F1]);
        pthread_mutex_unlock(&philo->data->mforks[F2]);
        return (-1);
    }
    time_print_diff(philo, FORK2);
    time_print_diff(philo, EATING);

    pthread_mutex_lock(&philo->data->mdeath);
    philo->time_to_live = time_current_long() + philo->data->time_to_die; //protect ttl
    pthread_mutex_unlock(&philo->data->mdeath);
    csleep(philo->data->time_to_eat, philo);
    pthread_mutex_unlock(&philo->data->mforks[F1]);
    pthread_mutex_unlock(&philo->data->mforks[F2]);
    return (1);
}

int ft_sleep(struct s_philosopher *philo)
{
    time_print_diff(philo, SLEAPING);
    csleep(philo->data->time_to_sleep, philo);
    return (1);
}

int    ft_think(struct s_philosopher *philo)
{
    time_print_diff(philo, THINKING);
    return (1);
}