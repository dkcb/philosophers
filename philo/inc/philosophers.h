/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkocob <dkocob@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/14 21:23:36 by dkocob        #+#    #+#                 */
/*   Updated: 2022/12/14 21:43:32 by dkocob        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <errno.h>
# include <sys/wait.h>
# include <sys/time.h>
# include <pthread.h>

# define FORK1 101
# define FORK2 102
# define EATING 10
# define STOPEATING 11
# define SLEAPING 20
# define STOPSLEAPING 21
# define THINKING 3
# define DIED 0

struct s_philosopher
{
	int							index;
	long						time_to_live;
	int							eat_count;
	struct s_data				*data;
};

struct s_data
{
	int							dead;
	int							time_to_eat;
	int							time_to_sleep;
	int							time_to_die;
	int							meals_total;
	int							number_of_philosophers;
	struct s_philosopher		*philo_arr;
	pthread_mutex_t				*mforks;
	pthread_t					*tarr;
	pthread_mutex_t				mprint;
	pthread_mutex_t				mdeath;
	long						time_start_long;
};

int		ft_atoi(const char *str);
void	csleep(int ms, struct s_philosopher *philo);
void	*ft_phil_routine(void *val);
void	*death_thread(void *val);
int		init(int argc, char **argv, struct s_data *data);
int		cleaning(struct s_data *data);
int		init_tarr(struct s_data *data);
int		init_philo(struct s_data *data);
int		init_forks(struct s_data *data);
int		time_print_diff(struct s_philosopher *philo, int action);
int		ft_eat(struct s_philosopher *philo);
int		ft_sleep(struct s_philosopher *philo);
int		ft_think(struct s_philosopher *philo);
long	time_cl(void);
int		death_check(struct s_data *data);
#endif
