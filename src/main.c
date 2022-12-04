/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkocob <dkocob@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/09 18:51:34 by dkocob        #+#    #+#                 */
/*   Updated: 2022/12/04 20:43:58 by dkocob        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"


 
    // printf("%l%02dms ", 1123);
    // time_print_diff(&philo->data->time_from_start, &philo->time_current);
    // printf(" philo %d not eat for %ld ms, of max %d ms --- \n", philo->index, (philo->time_current.tv_sec - philo->last_meal.tv_sec) * 1000 + (philo->time_current.tv_usec - philo->last_meal.tv_usec) / 1000, philo->data->time_to_die);
            // printf(" philo %d is dead\n \n \n", philo->index);
// void time_print_diff(struct s_philosopher *philo, struct timeval *time_from_start, struct timeval *time_current, int action)
    // printf("%ld%02dms ", time_current->tv_sec - time_from_start->tv_sec, time_current->tv_usec/1000);
    // ft_putnbr_fd((int)time_current->tv_sec - time_from_start->tv_sec, 1);
    // ft_putnbr_fd((int)time_current->tv_usec/1000, 1);
    // ft_putstr_fd(" ms", 1);
void time_print_diff(struct s_philosopher *philo, int action)
{
    pthread_mutex_lock(philo->data->mprint);
    gettimeofday(&philo->time_current, NULL);
    printf("%ld%02dms ", philo->time_current.tv_sec - philo->data->time_from_start.tv_sec, philo->time_current.tv_usec/1000);
    if (action == 0)
        printf(" Philo %d is dead\n", philo->index);
    if (action == 1)
        printf(" philo %d is eating\n", philo->index);
    if (action == 2)
        printf(" Philo %d is sleeping\n", philo->index);
    if (action == 3)
        printf(" Philo %d is thinking\n", philo->index);
    pthread_mutex_unlock(philo->data->mprint);
}

void ft_phil_init(struct s_philosopher *phil, struct s_data *data, int index)
{
    gettimeofday(&data->time_from_start, NULL);
    gettimeofday(&phil->last_meal, NULL);
    phil->index = index + 1;
    phil->eat_count = 0;
    phil->data = data;
    data->dead = 0;
}

int    ft_check_death(struct s_philosopher *philo)
{
    if ((philo->time_current.tv_sec - philo->last_meal.tv_sec) * 1000 + (philo->time_current.tv_usec - philo->last_meal.tv_usec) / 1000 > philo->data->time_to_die)
    {
        pthread_mutex_lock(philo->data->mdead);
        if (philo->data->dead == 0)
            time_print_diff(philo, 0);
        philo->data->dead = 1;
        pthread_mutex_unlock(philo->data->mdead);
        return (1);
    }
    return (0);
}

void    ft_eat(struct s_philosopher *philo)
{
    pthread_mutex_lock(&philo->data->mforks[philo->index - 1]);
    if (ft_check_death(philo))
    {
        pthread_mutex_unlock(&philo->data->mforks[philo->index - 1]);
        return ;
    }
    time_print_diff(philo, 1);
    usleep(philo->data->time_to_eat * 1000);
    gettimeofday(&philo->last_meal, NULL);
    pthread_mutex_unlock(&philo->data->mforks[philo->index - 1]);
}

void    ft_sleep(struct s_philosopher *philo)
{
    if (ft_check_death(philo))
            return ;
    time_print_diff(philo, 2);
    usleep(philo->data->time_to_sleep * 1000);
}

void    ft_think(struct s_philosopher *philo)
{
    if (ft_check_death(philo))
        return ;
    time_print_diff(philo, 3);
}

void *ft_phil_routine(void *val)
{
    struct s_philosopher *philo = (struct s_philosopher *)val;

    while (philo->eat_count < philo->data->meals_total)
    {

        ft_eat(philo);
        philo->eat_count++;
        ft_sleep(philo);
        ft_think(philo);
    }
    return (NULL);
}

int main (int argc, char **argv) 
{
    int                     number_of_philosophers = ft_atoi(argv[1]);
    struct s_philosopher    phil[number_of_philosophers];
    pthread_t               threads[number_of_philosophers];
    pthread_mutex_t         mforks[number_of_philosophers];
    pthread_mutex_t         mprint;
    pthread_mutex_t         mdead;
    struct s_data           data;
    int                     i = 1;
    int                     j = 0;

    pthread_mutex_init(&mdead, NULL);
    pthread_mutex_init(&mprint, NULL);
    data.mdead = &mdead;
    data.mprint = &mprint;
    if (argc < 3 || argc > 6)
        return (write(2, "Wrong arguments!\n", 17));
    while (argv[i])
    {
        while(argv[i][j] != '\0')
        {
            if (argv[i][j] >= '0' && argv[i][j] <= '9')
                j++;
            else 
                return (write(2, "Wrong input!\n", 13));
        }
        j = 0;
        i++;
    }
    data.time_to_die = ft_atoi(argv[2]);
    data.time_to_eat = ft_atoi(argv[3]);
    data.time_to_sleep = ft_atoi(argv[4]);
    data.meals_total = ft_atoi(argv[5]);
    data.mforks = &mforks[0];
 
    i = 0;
    while (i < number_of_philosophers)
    {
        ft_phil_init(&phil[i], &data, i);
        pthread_mutex_init(&mforks[i], NULL);
        i++;
    }
    i = 0;
    while (i < number_of_philosophers)
    {
        if (pthread_create(&threads[i], NULL, &ft_phil_routine, &phil[i]) != 0)
        {
            perror("thread creation fails!\n");
            return (1);
        }
        i++;
    }
    i = 0;
    while (i < number_of_philosophers)
    {
        if (pthread_join(threads[i], NULL))
        {
            perror("thread join fails!\n");
            return (2);
        }
        // printf("thread joined\n");
        i++;
    }
    i = 0;
    while (i < number_of_philosophers)
    {
        pthread_mutex_destroy(&mforks[i]);
        i++;
    }
    pthread_mutex_destroy(data.mprint);
    pthread_mutex_destroy(data.mdead);
    return 0;
}

// void    ft_eat(struct s_philosopher *philo)
// {
//     pthread_mutex_lock(&philo->data->mforks[philo->index - 1]);
//     if (ft_check_death(philo))
//         return ;
//     usleep(philo->data->time_to_eat * 1000);
//     gettimeofday(&philo->last_meal, NULL);
//     pthread_mutex_unlock(&philo->data->mforks[philo->index - 1]);
//     pthread_mutex_lock(philo->data->mprint);
//     gettimeofday(&philo->time_current, NULL);
//     // printf("%ld%02dms ", philo->time_current.tv_sec - philo->data->time_from_start.tv_sec, philo->time_current.tv_usec/1000);
//     time_print_diff(&philo->data->time_from_start, &philo->time_current);
//     printf(" philo %d is eating\n", philo->index);
//     pthread_mutex_unlock(philo->data->mprint);
// }