/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkocob <dkocob@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/09 18:51:34 by dkocob        #+#    #+#                 */
/*   Updated: 2022/12/12 21:24:56 by dkocob        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

long time_vs_current(struct timeval *t2)
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
    printf("%ld", time_vs_current(&philo->data->time_from_start));
    if (action == 0)
    {   
        if (philo->data->dead == 0)
        {
            printf(" === philo %d, did not eat %ldms of %dms\n", philo->index, time_vs_current(&philo->last_meal), philo->data->time_to_die);
            printf(" %d died\n", philo->index);
        }
        philo->data->dead = 1;
        pthread_mutex_unlock(philo->data->mprint);
        return (1);
    }
    if (action == 101)
        printf(" %d has taken a fork1\n", philo->index);
    if (action == 102)
        printf(" %d has taken a fork2\n", philo->index);
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
    pthread_mutex_unlock(philo->data->mprint);
    return (0);
}

void ft_phil_init(struct s_philosopher *philo, struct s_data *data, int index)
{
    gettimeofday(&philo->last_meal, NULL);
    
    philo->time_to_live = philo->last_meal.tv_sec * 1000 + philo->last_meal.tv_usec / 1000 + data->time_to_die;
    philo->index = index + 1;
    philo->eat_count = data->meals_total;
    philo->data = data;
    data->dead = 0;
}

int ft_check_death(struct s_philosopher *philo)
{
    // if (philo->data) > philo->data->time_to_die)
    //     return (time_print_diff(philo, DIED));
    if (time_vs_current(&philo->last_meal) > philo->data->time_to_die)
        return (time_print_diff(philo, DIED));
    return (0);
}

int csleep(int ms, long *ttl)
{
    long end;
    int dead;
    struct timeval cur;

    dead = 0;
    gettimeofday(&cur, NULL);
    if (ms > ttl)
    {
        end = cur.tv_sec * 1000 + cur.tv_usec / 1000  + ttl;
        dead = 1;
    }
    else
    {
        end = cur.tv_sec * 1000 + cur.tv_usec / 1000  + ms;
        ttl = ttl - ms;
    }
    while (cur.tv_sec * 1000 + cur.tv_usec / 1000 <= end)
    {
        usleep(250);
        gettimeofday(&cur, NULL);
    }
    return (dead);
}

int    ft_eat(struct s_philosopher *philo)
{
    pthread_mutex_lock(&philo->data->mforks[F1]);
    if (ft_check_death(philo))
    {
        pthread_mutex_unlock(&philo->data->mforks[F1]);
        return (-1);
    }
    time_print_diff(philo, FORK1); //???
    pthread_mutex_lock(&philo->data->mforks[F2]);
    if (ft_check_death(philo))
    {
        pthread_mutex_unlock(&philo->data->mforks[F1]);
        pthread_mutex_unlock(&philo->data->mforks[F2]);
        return (-1);
    }
    time_print_diff(philo, FORK2);
    time_print_diff(philo, EATING);
    gettimeofday(&philo->last_meal, NULL);
    if (csleep(philo->data->time_to_eat, philo->time_to_live))
        return (time_print_diff(philo, DIED));
    pthread_mutex_unlock(&philo->data->mforks[F1]);
    pthread_mutex_unlock(&philo->data->mforks[F2]);
    return (1);
}

int ft_sleep(struct s_philosopher *philo)
{
    struct timeval cur;
    
    time_print_diff(philo, SLEAPING);
    if (csleep(philo->data->time_to_sleep, philo->time_to_live))
        return (time_print_diff(philo, DIED));
    // time_print_diff(philo, STOPEATING);
    return (1);
}

int    ft_think(struct s_philosopher *philo)
{
    if (ft_check_death(philo))
        return (-1);
    // while (cur.tv_sec * 1000 + cur.tv_usec / 1000 <= end)
    // {
    //     usleep(250);
    //     gettimeofday(&cur, NULL);
    // }
    time_print_diff(philo, 3);
    return (1);
}

void *ft_phil_routine(void *val)
{
    struct s_philosopher *philo = (struct s_philosopher *)val;

    while (philo->eat_count != 0)
    {
        if (!ft_eat(philo))
            return (NULL);
        philo->eat_count--;
        if (!ft_sleep(philo))
            return (NULL);
        if (!ft_think(philo))
            return (NULL);
    }
    return (NULL);
}

int main (int argc, char **argv) 
{
    struct s_philosopher    phil[201];
    pthread_t               threads[201];
    pthread_mutex_t         mforks[201];
    pthread_mutex_t         mprint;
    struct s_data           data;
    int                     i = 1;
    int                     j = 0;

    if (argc < 5 || argc > 6 || ft_atoi(argv[1]) > 200)
        return (write(2, "Wrong arguments!\n", 17));
    gettimeofday(&data.time_from_start, NULL);
    data.start_time_long = (data.time_from_start.tv_sec * 1000 + data.time_from_start.tv_usec / 1000);
    data.mforks = &mforks[0];
    data.mprint = &mprint;
    data.meals_total = -1;
    while (argv[i])
    {
        while(argv[i][j] != '\0')
        {
            if (argv[i][j] >= '0' && argv[i][j] <= '9' && argv[i][j] != '\0')
                j++;
            else 
                return (write(2, "Wrong input!\n", 13));
        }
        j = 0;
        i++;
    }
    data.number_of_philosophers = ft_atoi(argv[1]);
    data.time_to_die = ft_atoi(argv[2]);
    data.time_to_eat = ft_atoi(argv[3]);
    data.time_to_sleep = ft_atoi(argv[4]);
    if (argv[5])
      data.meals_total = ft_atoi(argv[5]);
    if (data.number_of_philosophers == 1)
    {
        printf("0 1 has taken a fork\n");
        csleep(data.time_to_sleep, data.time_to_die);
        printf("%d 1 died\n", data.time_to_die);
        return (0);
    }
    pthread_mutex_init(&mprint, NULL);
    i = 0;
    while (i < data.number_of_philosophers)
    {
        ft_phil_init(&phil[i], &data, i);
        if (pthread_mutex_init(&mforks[i], NULL) !=0)
            return (write(2, "Mutex init fail!\n", 17));
        usleep (i % 2 * data.time_to_eat);
        if (pthread_create(&threads[i], NULL, &ft_phil_routine, &phil[i]) != 0)
        {
            perror("thread creation fails!\n");
            return (1);
        }
        i++;
    }
    i = 0;
    while (i < data.number_of_philosophers)
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
    while (i < data.number_of_philosophers)
    {
        pthread_mutex_destroy(&mforks[i]);
        i++;
    }
    pthread_mutex_destroy(data.mprint);
    return (0);
}
    // pthread_mutex_init(&mprint, NULL);
    // i = 0;
    // while (i < data.number_of_philosophers)
    // {
    //     ft_phil_init(&phil[i], &data, i);
    //     if (pthread_mutex_init(&mforks[i], NULL) !=0)
    //         return (write(2, "Mutex init fail!\n", 17));
    //     i++;
    // }
    // i = 0;
    // while (i < data.number_of_philosophers)
    // {
    //     usleep (i % 2 * 5);
    //     if (pthread_create(&threads[i], NULL, &ft_phil_routine, &phil[i]) != 0)
    //     {
    //         perror("thread creation fails!\n");
    //         return (1);
    //     }
    //     i++;
    // }
    // long time_diff(struct timeval *t2, struct timeval *t1)
// {
//     return ((t1->tv_sec - t2->tv_sec) * 1000 + (t1->tv_usec - t2->tv_usec) / 1000);
// }

// int csleep(int ms, struct timeval last_meal, int ttd, long *ttl)
// {
//     long end;
//     long lastm;
//     int dead = 0;
//     struct timeval cur;

//     lastm = last_meal.tv_sec * 1000 + last_meal.tv_usec / 1000;
//     gettimeofday(&cur, NULL);
//     end = cur.tv_sec * 1000 + cur.tv_usec / 1000  + ms;
//     if (end - lastm > ttd)
//     {
//         dead = 1;
//         printf("--- End:%ld, lastm:%ld, ttd: %d, diff:%d, diff_TTD:%d ---\n", end, lastm, ttd, ttd, ttd);
//         end = lastm + ttd;
//     }
//     while (cur.tv_sec * 1000 + cur.tv_usec / 1000 <= end)
//     {
//         usleep(250);
//         gettimeofday(&cur, NULL);
//     }
//     return (dead);
// }
