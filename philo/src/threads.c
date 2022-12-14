/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   threads.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkocob <dkocob@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/14 21:24:58 by dkocob        #+#    #+#                 */
/*   Updated: 2022/12/14 22:09:44 by dkocob        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	*death_thread(void *val)
{
	struct s_data	*d;
	int				i;

	d = (struct s_data *)val;
	while (!death_check(d))
	{
		i = 0;
		while (i < d->p_qty - 1)
		{
			if (d->p_arr[i].time_to_live < time_cl())
			{
				d->dead++;
				pthread_mutex_lock(&d->mprint);
				if (d->dead == 1)
					printf ("%5ld %d died\n", time_cl() - d->time_start, i + 1);
				pthread_mutex_unlock(&d->mprint);
			}
			i++;
		}
		pthread_mutex_unlock(&d->mdeath);
		usleep(50);
	}
	return (NULL);
}

void	*ft_phil_routine(void *val)
{
	struct s_philosopher	*philo;

	philo = (struct s_philosopher *)val;
	while (philo->eat_count != 0 && !death_check(philo->d))
	{
		ft_eat(philo);
		philo->eat_count--;
		if (death_check(philo->d))
			return (NULL);
		ft_sleep(philo);
		if (death_check(philo->d))
			return (NULL);
		ft_think(philo);
		if (death_check(philo->d))
			return (NULL);
	}
	return (NULL);
}

int	init_tarr(struct s_data *d)
{
	int	i;

	i = 0;
	while (i < d->p_qty)
	{
		if (pthread_create(&d->tarr[i], NULL,
				&ft_phil_routine, &d->p_arr[i]) != 0)
		{
			perror("thread creation fails!\n");
			return (1);
		}
		i++;
	}
	if (pthread_create(&d->tarr[220], NULL, &death_thread, d) != 0)
	{
		perror("thread creation fails!\n");
		return (1);
	}
	return (0);
}
