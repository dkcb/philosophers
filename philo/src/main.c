/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkocob <dkocob@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/14 21:24:50 by dkocob        #+#    #+#                 */
/*   Updated: 2022/12/14 21:54:28 by dkocob        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

long	time_cl(void)
{
	struct timeval	current;

	gettimeofday(&current, NULL);
	return ((current.tv_sec) * 1000 + (current.tv_usec) / 1000);
}

int	time_print_diff(struct s_philosopher *philo, int action)
{
	pthread_mutex_lock(&philo->d->mprint);
	if (death_check(philo->d))
	{
		pthread_mutex_unlock(&philo->d->mprint);
		return (1);
	}
	printf ("%5ld", time_cl() - philo->d->time_start);
	if (action == 101)
		printf(" %d has taken a fork\n", philo->index);
	if (action == 102)
		printf(" %d has taken a fork\n", philo->index);
	if (action == 10)
		printf(" %d is eating\n", philo->index);
	if (action == 11)
		printf(" %d stoped eating --\n", philo->index);
	if (action == 20)
		printf(" %d is sleeping\n", philo->index);
	if (action == 21)
		printf(" %d stoppped sleeping\n", philo->index);
	if (action == 3)
		printf(" %d is thinking\n", philo->index);
	pthread_mutex_unlock(&philo->d->mprint);
	return (0);
}

void	csleep(int ms, struct s_philosopher *philo)
{
	long	end;

	end = time_cl() + (long)ms;
	if (end > philo->time_to_live)
		end = philo->time_to_live + 500;
	while (time_cl() < end)
		usleep(250);
}

int	main(int argc, char **argv)
{
	struct s_philosopher	phil[201];
	pthread_t				tarr[201];
	pthread_mutex_t			mforks[201];
	struct s_data			d;

	d.p_arr = &phil[0];
	d.tarr = &tarr[0];
	d.mforks = &mforks[0];
	pthread_mutex_init(&d.mprint, NULL);
	pthread_mutex_init(&d.mdeath, NULL);
	if (init(argc, argv, &d) != 0)
		return (-1);
	if (d.p_qty == 1)
	{
		printf("0 1 has taken a fork\n");
		usleep(d.time_to_die * 1000);
		printf("%d 1 died\n", d.time_to_die);
		return (0);
	}
	init_tarr(&d);
	cleaning(&d);
	pthread_mutex_destroy(&d.mprint);
	pthread_mutex_destroy(&d.mdeath);
	return (0);
}
