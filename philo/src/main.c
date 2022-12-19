/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkocob <dkocob@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/14 21:24:50 by dkocob        #+#    #+#                 */
/*   Updated: 2022/12/19 15:04:52 by dkocob        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

long	time_cl(void)
{
	struct timeval	current;

	gettimeofday(&current, NULL);
	return (current.tv_sec * 1000 + current.tv_usec / 1000);
}

int	time_print_diff(struct s_philosopher *philo, int action)
{
	if (death_check(philo->d))
		return (1);
	pthread_mutex_lock(&philo->d->mprint);
	if (death_check(philo->d))
	{
		pthread_mutex_unlock(&philo->d->mprint);
		return (1);
	}
	printf ("%ld", time_cl() - philo->d->time_start);
	if (action == 101)
		printf(" %d has taken a fork\n", philo->indx);
	if (action == 102)
		printf(" %d has taken a fork\n", philo->indx);
	if (action == 10)
		printf(" %d is eating\n", philo->indx);
	if (action == 11)
		printf(" %d stoped eating --\n", philo->indx);
	if (action == 20)
		printf(" %d is sleeping\n", philo->indx);
	if (action == 21)
		printf(" %d stoppped sleeping\n", philo->indx);
	if (action == 3)
		printf(" %d is thinking\n", philo->indx);
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
	struct s_data	d;

	if (argc < 5 || argc > 6 || ft_atoi(argv[1]) > 200 || ft_atoi(argv[1]) < 1
		|| ft_atoi(argv[2]) < 1 || ft_atoi(argv[3]) < 1
		|| ft_atoi(argv[4]) < 1)
		return (write(2, "Wrong arguments!\n", 17));
	if (init(argv, &d, 1) != 0)
		return (-1);
	if (ft_atoi(argv[1]) == 1)
	{
		printf("0 1 has taken a fork\n");
		usleep(ft_atoi(argv[2]) * 1000);
		printf("%d 1 died\n", ft_atoi(argv[2]));
		return (0);
	}
	init_tarr(&d);
	cleaning(&d, 0);
	return (0);
}
