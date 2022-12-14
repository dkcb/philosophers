/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkocob <dkocob@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/13 15:34:29 by dkocob        #+#    #+#                 */
/*   Updated: 2022/12/14 20:51:11 by dkocob        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

int init_forks(struct s_data *data)
{
    int i;

    i = 0;
    while (i < data->number_of_philosophers)
    {
        if (pthread_mutex_init(&data->mforks[i], NULL) != 0)
        {
            while (i > - 1)
            {
                pthread_mutex_destroy(&data->mforks[i]);
                i--;
            }    
            return (write(2, "Mutex init fail!\n", 17));
        }
        i++;
    }
    return (0);
}

int init_philo(struct s_data *data)
{
    int i;
    
    i = 0;
    while (i < data->number_of_philosophers)
    {
        data->philo_arr[i].time_to_live = time_current_long() + data->time_to_die;
        data->philo_arr[i].index = i + 1;
        data->philo_arr[i].eat_count = data->meals_total;
        data->philo_arr[i].data = data;
        i++;
    }
    return (0);
}

int init(int argc, char **argv, struct s_data *data)
{
    int i;
    int j;

    if (argc < 5 || argc > 6 || ft_atoi(argv[1]) > 200)
        return (write(2, "Wrong arguments!\n", 17));
    data->time_start_long = time_current_long();
    data->meals_total = -1;
    i = 1;
    while (argv[i])
    {
        j = 0;
        while(argv[i][j] != '\0')
        {
            if (argv[i][j] >= '0' && argv[i][j] <= '9' && argv[i][j] != '\0')
                j++;
            else 
                return (write(2, "Wrong input!\n", 13));
        }
        i++;
    }
    data->dead = 0;
    data->number_of_philosophers = ft_atoi(argv[1]);
    data->time_to_die = ft_atoi(argv[2]);
    data->time_to_eat = ft_atoi(argv[3]);
    data->time_to_sleep = ft_atoi(argv[4]);
    if (argv[5])
      data->meals_total = ft_atoi(argv[5]);
    if (init_philo(data))
        return (-1);
    if (init_forks(data) != 0)
        return (-1);
    return (0);
}
