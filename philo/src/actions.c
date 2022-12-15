/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   actions.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkocob <dkocob@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/14 21:24:14 by dkocob        #+#    #+#                 */
/*   Updated: 2022/12/15 18:57:27 by dkocob        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

int	ft_eat(struct s_philosopher *philo)
{
	usleep ((philo->indx + 1) % 2 * philo->d->time_to_eat * 10);
	pthread_mutex_lock(&philo->d->mforks[philo->indx - 1]);
	if (death_check(philo->d))
	{
		pthread_mutex_unlock(&philo->d->mforks[philo->indx - 1]);
		return (-1);
	}
	time_print_diff(philo, FORK1);
	pthread_mutex_lock(&philo->d->mforks[philo->indx % philo->d->p_tot]);
	if (death_check(philo->d))
	{
		pthread_mutex_unlock(&philo->d->mforks[philo->indx - 1]);
		pthread_mutex_unlock(&philo->d->mforks[philo->indx % philo->d->p_tot]);
		return (-1);
	}
	time_print_diff(philo, FORK2);
	time_print_diff(philo, EATING);
	pthread_mutex_lock(&philo->d->mdeath);
	philo->time_to_live = time_cl() + philo->d->time_to_die;
	philo->eat_count--;
	pthread_mutex_unlock(&philo->d->mdeath);
	csleep(philo->d->time_to_eat, philo);
	pthread_mutex_unlock(&philo->d->mforks[philo->indx - 1]);
	pthread_mutex_unlock(&philo->d->mforks[philo->indx % philo->d->p_tot]);
	return (1);
}

int	ft_sleep(struct s_philosopher *philo)
{
	time_print_diff(philo, SLEAPING);
	csleep(philo->d->time_to_sleep, philo);
	return (1);
}

int	ft_think(struct s_philosopher *philo)
{
	time_print_diff(philo, THINKING);
	return (1);
}
