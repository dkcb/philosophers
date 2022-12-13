/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   actions.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkocob <dkocob@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/13 18:16:00 by dkocob        #+#    #+#                 */
/*   Updated: 2022/12/13 18:16:10 by dkocob        ########   odam.nl         */
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
    gettimeofday(&philo->last_meal, NULL);
    philo->time_to_live = philo->last_meal.tv_sec * 1000 + philo->last_meal.tv_usec / 1000 + philo->data->time_to_die;
    if (csleep(philo->data->time_to_eat, &philo->time_to_live))
        return (time_print_diff(philo, DIED));
    pthread_mutex_unlock(&philo->data->mforks[F1]);
    pthread_mutex_unlock(&philo->data->mforks[F2]);
    return (1);
}

int ft_sleep(struct s_philosopher *philo)
{
    // struct timeval cur;
    
    time_print_diff(philo, SLEAPING);
    if (csleep(philo->data->time_to_sleep, &philo->time_to_live))
        return (time_print_diff(philo, DIED));
    // time_print_diff(philo, STOPEATING);
    return (1);
}

int    ft_think(struct s_philosopher *philo)
{
    if (ft_check_death(philo))
        return (-1);
    // while (cur.tv_sec * 1000 + cur.tv_usec / 1000 <= end)
    // {
    //     usleep(250);
    //     gettimeofday(&cur, NULL);
    // }
    time_print_diff(philo, 3);
    return (1);
}