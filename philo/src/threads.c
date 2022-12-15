/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   threads.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkocob <dkocob@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/14 21:24:58 by dkocob        #+#    #+#                 */
/*   Updated: 2022/12/15 17:44:56 by dkocob        ########   odam.nl         */
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
		while (i < d->p_tot - 1)
		{
			pthread_mutex_lock(&d->mdeath);
			if (d->p_arr[i].time_to_live < time_cl())
			{
				d->dead++;
				if (d->dead == 1 && d->p_arr[i].eat_count != 0)
					printf ("%ld %d died\n", time_cl() - d->time_start, i + 1);
			}
			i++;
			pthread_mutex_unlock(&d->mdeath);
		}
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
	while (i < d->p_tot)
	{
		if (pthread_create(&d->tarr[i], NULL,
				&ft_phil_routine, &d->p_arr[i]) != 0)
		{
			perror("thread creation fails!\n");
			return (1);
		}
		i++;
	}
	if (pthread_create(&d->tarr[200], NULL, &death_thread, d) != 0)
	{
		perror("thread creation fails!\n");
		return (1);
	}
	return (0);
}
