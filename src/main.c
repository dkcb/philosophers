/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkocob <dkocob@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/09 18:51:34 by dkocob        #+#    #+#                 */
/*   Updated: 2022/12/07 22:13:24 by dkocob        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

long time_diff(struct timeval *t2)
{
    struct timeval current;
    
    gettimeofday(&current, NULL);
    return ((current.tv_sec - t2->tv_sec) * 1000 + (current.tv_usec - t2->tv_usec) / 1000);
}
int time_print_diff(struct s_philosopher *philo, int action)
{
    pthread_mutex_lock(philo->data->mprint);
    if (philo->data->dead == 1)
    {
        pthread_mutex_unlock(philo->data->mprint);
        return (1);
    }
    printf("%ldms", time_diff(&philo->data->time_from_start));
    if (action == 0)
    {   
        if (philo->data->dead == 0)
        {
            printf(" === philo %d, last time eat is %ldms\n", philo->index, time_diff(&philo->last_meal));
            printf(" Philo %d is dead\n", philo->index);
        }
        philo->data->dead = 1;
        pthread_mutex_unlock(philo->data->mprint);
        return (1);
    }
    if (action == 10)
        printf(" philo %d started eating\n", philo->index);
    if (action == 11)
        printf(" philo %d stoped eating\n", philo->index);
    if (action == 20)
        printf(" Philo %d started sleeping\n", philo->index);
    if (action == 21)
        printf(" Philo %d stoppped sleeping\n", philo->index);
    if (action == 3)
        printf(" Philo %d is thinking\n", philo->index);
    pthread_mutex_unlock(philo->data->mprint);
    return (0);
}

void ft_phil_init(struct s_philosopher *philo, struct s_data *data, int index)
{
    gettimeofday(&philo->time_current, NULL);
    gettimeofday(&philo->last_meal, NULL);
    philo->index = index + 1;
    philo->eat_count = 0;
    philo->data = data;
    data->dead = 0;
}

int ft_check_death(struct s_philosopher *philo)
{
    if (time_diff(&philo->last_meal) > philo->data->time_to_die)
        return (time_print_diff(philo, 0));
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
    time_print_diff(philo, 10);
    usleep(philo->data->time_to_eat * 1000);
    time_print_diff(philo, 11);
    gettimeofday(&philo->last_meal, NULL);
    pthread_mutex_unlock(&philo->data->mforks[philo->index - 1]);
}

void    ft_sleep(struct s_philosopher *philo)
{
    if (ft_check_death(philo))
            return ;
    time_print_diff(philo, 20);
    usleep(philo->data->time_to_sleep * 1000);
    time_print_diff(philo, 21);
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

        if (ft_check_death(philo))
            return (NULL);
        ft_eat(philo);
        philo->eat_count++;
        if (ft_check_death(philo))
            return (NULL);
        ft_sleep(philo);
        if (ft_check_death(philo))
            return (NULL);
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

    gettimeofday(&data.time_from_start, NULL);
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
        printf("thread joined\n");
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
