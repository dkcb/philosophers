/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   actions.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkocob <dkocob@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/14 21:24:14 by dkocob        #+#    #+#                 */
/*   Updated: 2022/12/14 21:37:51 by dkocob        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

int	ft_eat(struct s_philosopher *philo)
{
	usleep ((philo->index + 1) % 2 * 200);
	pthread_mutex_lock(&philo->data->mforks[philo->index - 1]);
	if (death_check(philo->data))
	{
		pthread_mutex_unlock(&philo->data->mforks[philo->index - 1]);
		return (-1);
	}
	time_print_diff(philo, FORK1);
	pthread_mutex_lock(&philo->data->mforks[philo->index % philo->data->number_of_philosophers]);
	if (death_check(philo->data))
	{
		pthread_mutex_unlock(&philo->data->mforks[philo->index - 1]);
		pthread_mutex_unlock(&philo->data->mforks[philo->index % philo->data->number_of_philosophers]);
		return (-1);
	}
	time_print_diff(philo, FORK2);
	time_print_diff(philo, EATING);
	pthread_mutex_lock(&philo->data->mdeath);
	philo->time_to_live = time_cl() + philo->data->time_to_die;
	pthread_mutex_unlock(&philo->data->mdeath);
	csleep(philo->data->time_to_eat, philo);
	pthread_mutex_unlock(&philo->data->mforks[philo->index - 1]);
	pthread_mutex_unlock(&philo->data->mforks[philo->index % philo->data->number_of_philosophers]);
	return (1);
}

int	ft_sleep(struct s_philosopher *philo)
{
	time_print_diff(philo, SLEAPING);
	csleep(philo->data->time_to_sleep, philo);
	return (1);
}

int	ft_think(struct s_philosopher *philo)
{
	time_print_diff(philo, THINKING);
	return (1);
}
