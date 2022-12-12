/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkocob <dkocob@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/09 18:51:34 by dkocob        #+#    #+#                 */
/*   Updated: 2022/12/12 19:25:20 by dkocob        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

long time_vs_current(struct timeval *t2)
{
    struct timeval current;
    
    gettimeofday(&current, NULL);
    return ((current.tv_sec - t2->tv_sec) * 1000 + (current.tv_usec - t2->tv_usec) / 1000);
}

long time_diff(struct timeval *t2, struct timeval *t1)
{
    return ((t1->tv_sec - t2->tv_sec) * 1000 + (t1->tv_usec - t2->tv_usec) / 1000);
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
            // printf(" === philo %d, did not eat %ldms of %dms\n", philo->index, time_vs_current(&philo->last_meal), philo->data->time_to_die);
            printf(" %d died\n", philo->index);
        }
        philo->data->dead = 1;
        pthread_mutex_unlock(philo->data->mprint);
        return (1);
    }
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
    pthread_mutex_unlock(philo->data->mprint);
    return (0);
}

void ft_phil_init(struct s_philosopher *philo, struct s_data *data, int index)
{
    gettimeofday(&philo->time_current, NULL);
    gettimeofday(&philo->last_meal, NULL);
    philo->index = index + 1;
    philo->eat_count = data->meals_total;
    philo->data = data;
    data->dead = 0;
}

int ft_check_death(struct s_philosopher *philo)
{
    if (time_vs_current(&philo->last_meal) > philo->data->time_to_die)
        return (time_print_diff(philo, DIED));
    return (0);
}

int csleep(int ms, struct timeval last_meal, int ttd)
{
    long end;
    long lastm;
    int dead = 0;
    struct timeval cur;

    lastm = last_meal.tv_sec * 1000 + last_meal.tv_usec / 1000;
    gettimeofday(&cur, NULL);
    end = cur.tv_sec * 1000 + cur.tv_usec / 1000  + ms;
    if (end - lastm > ttd)
    {
        dead = 1;
        // printf("--- End:%ld, lastm:%ld, ttd: %d, diff:%d, diff_TTD:%d ---\n", end, lastm, ttd, ttd, ttd);
        end = lastm + ttd + 1;
    }
    while (cur.tv_sec * 1000 + cur.tv_usec / 1000 <= end)
    {
        usleep(250);
        gettimeofday(&cur, NULL);
    }
    return (dead);
}

void    ft_eat(struct s_philosopher *philo)
{
    pthread_mutex_lock(&philo->data->mforks[F1]);
    time_print_diff(philo, FORK1);
    if (ft_check_death(philo))
    {
        pthread_mutex_unlock(&philo->data->mforks[F1]);
        return ;
    }
    pthread_mutex_lock(&philo->data->mforks[F2]);
    if (ft_check_death(philo))
    {
        pthread_mutex_unlock(&philo->data->mforks[F1]);
        pthread_mutex_unlock(&philo->data->mforks[F2]);
        return ;
    }
    time_print_diff(philo, FORK2);
    time_print_diff(philo, EATING);
    gettimeofday(&philo->last_meal, NULL);
    if (csleep(philo->data->time_to_eat, philo->last_meal, philo->data->time_to_die))
        time_print_diff(philo, DIED);
    pthread_mutex_unlock(&philo->data->mforks[F1]);
    pthread_mutex_unlock(&philo->data->mforks[F2]);
}

void    ft_sleep(struct s_philosopher *philo)
{
    time_print_diff(philo, SLEAPING);
    if (csleep(philo->data->time_to_sleep, philo->last_meal, philo->data->time_to_die))
        time_print_diff(philo, DIED);

    // time_print_diff(philo, STOPEATING);
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

    while (philo->eat_count != 0)
    {
        if (ft_check_death(philo))
            return (NULL);
        ft_eat(philo);
        philo->eat_count--;
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
    struct s_philosopher    phil[201];
    pthread_t               threads[201];
    pthread_mutex_t         mforks[201];
    pthread_mutex_t         mprint;
    pthread_mutex_t         mdead;
    struct s_data           data;
    int                     i = 1;
    int                     j = 0;

    if (argc < 3 || argc > 6 || ft_atoi(argv[1]) > 200)
        return (write(2, "Wrong arguments!\n", 17));
    data.number_of_philosophers = ft_atoi(argv[1]);
    gettimeofday(&data.time_from_start, NULL);
    data.start_time_long = (data.time_from_start.tv_sec * 1000 + data.time_from_start.tv_usec / 1000);
    data.mforks = &mforks[0];
    data.mdead = &mdead;
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
    if (argv[2] && argv[3] && argv[4])
    {
        data.time_to_die = ft_atoi(argv[2]);
        data.time_to_eat = ft_atoi(argv[3]);
        data.time_to_sleep = ft_atoi(argv[4]);
    }
    if (argv[5])
      data.meals_total = ft_atoi(argv[5]);
 

    pthread_mutex_init(&mdead, NULL);
    pthread_mutex_init(&mprint, NULL);
    i = 0;
    while (i < data.number_of_philosophers)
    {
        ft_phil_init(&phil[i], &data, i);
        if (pthread_mutex_init(&mforks[i], NULL) !=0)
            return (write(2, "Mutex init fail!\n", 17));
        usleep (i % 2 * 5);
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
    pthread_mutex_destroy(data.mdead);
    return 0;
}

    // if(data.number_of_philosophers == 1)
    // {
    //     printf("0 philo1 has taken a fork\n");
    //     printf("0 philo1 has taken a fork\n");
    //     printf("%ld philo1 stoped eating --\n", data.time_to_die);
    //     return ();
    // }
    // long since;
    //4pm 4:30 time to sleep + currnet_tiem exceeds
    //set dead to time when max limit is reached 
    // if (time_diff(philo-> ,philo->data0->time_to_sleep)
    // survive = philo->data->time_to_die - philo->data->time_to_sleep - time_vs_current (&philo->last_meal);
    // since = time_vs_current (&philo->last_meal);
    // philo->data->time_to_die - philo->data->time_to_sleep - 
    // if (survive < 0)
    //     time_print_diff(philo, 0);
    // if (philo->data->time_to_die - time_vs_current (&philo->last_meal) - philo->data->time_to_eat)
    // {
    //     time_print_diff(philo, 10);
    //     return ;
    // }
    // int i = 0;

    // while (i < philo->data->time_to_sleep * 10)
    // {
    //     if (ft_check_death(philo))
    //             return ;
    //     usleep(100);
    //     i += 1;
    // }
// void    ft_eat(struct s_philosopher *philo)
// {
//     pthread_mutex_lock(&philo->data->mforks[F1]);
//     time_print_diff(philo, FORK1);
//     // if (ft_check_death(philo))
//     // {
//     //     pthread_mutex_unlock(&philo->data->mforks[F1]);
//     //     return ;
//     // }
//     pthread_mutex_lock(&philo->data->mforks[F2]);
//     // if (ft_check_death(philo))
//     // {
//     //     pthread_mutex_unlock(&philo->data->mforks[F2]);
//     //     return ;
//     // }
//     time_print_diff(philo, FORK2);
//     time_print_diff(philo, EATING);
//     csleep(philo->data->time_to_eat);
//     time_print_diff(philo, STOPEATING);
//     gettimeofday(&philo->last_meal, NULL);
//     pthread_mutex_unlock(&philo->data->mforks[F1]);
//     pthread_mutex_unlock(&philo->data->mforks[F2]);
// }