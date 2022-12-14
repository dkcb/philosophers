/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkocob <dkocob@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/14 21:24:31 by dkocob        #+#    #+#                 */
/*   Updated: 2022/12/14 22:17:07 by dkocob        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	init_d(struct s_data *d, char **argv)
{
	d->meals_total = -1;
	d->dead = 0;
	d->p_qty = ft_atoi(argv[1]);
	d->time_to_die = ft_atoi(argv[2]);
	d->time_to_eat = ft_atoi(argv[3]);
	d->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		d->meals_total = ft_atoi(argv[5]);
}

int	init_forks(struct s_data *d)
{
	int	i;

	i = 0;
	while (i < d->p_qty)
	{
		if (pthread_mutex_init(&d->mforks[i], NULL) != 0)
		{
			while (i > -1)
			{
				pthread_mutex_destroy(&d->mforks[i]);
				i--;
			}
			return (write(2, "Mutex init fail!\n", 17));
		}
		i++;
	}
	return (0);
}

int	init_philo(struct s_data *d)
{
	int	i;

	i = 0;
	while (i < d->p_qty)
	{
		d->p_arr[i].time_to_live = time_cl() + d->time_to_die;
		d->p_arr[i].index = i + 1;
		d->p_arr[i].eat_count = d->meals_total;
		d->p_arr[i].d = d;
		i++;
	}
	return (0);
}

int	init(int argc, char **argv, struct s_data *d)
{
	int	i;
	int	j;

	if (argc < 5 || argc > 6 || ft_atoi(argv[1]) > 200)
		return (write(2, "Wrong arguments!\n", 17));
	d->time_start = time_cl();
	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j] != '\0')
		{
			if (argv[i][j] >= '0' && argv[i][j] <= '9' && argv[i][j] != '\0')
				j++;
			else
				return (write(2, "Wrong input!\n", 13));
		}
		i++;
	}
	init_d(d, argv);
	if (init_philo(d))
		return (-1);
	if (init_forks(d) != 0)
		return (-1);
	return (0);
}
