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

// int csleep(int ms, int *ttl)
// {
//     long end;
//     int dead;
//     struct timeval cur;

//     printf("ttl1: %d", *ttl);
//     dead = 0;
//     gettimeofday(&cur, NULL);
//     if (ms > *ttl)
//     {
//         end = cur.tv_sec * 1000 + cur.tv_usec / 1000  + *ttl;
//         dead = 1;
//     }
//     else
//     {
//         end = cur.tv_sec * 1000 + cur.tv_usec / 1000  + ms;
//         *ttl = *ttl - ms;
//     }
//     while (cur.tv_sec * 1000 + cur.tv_usec / 1000 <= end)
//     {
//         usleep(250);
//         gettimeofday(&cur, NULL);
//     }
//     printf("ttl2: %d", *ttl);
//     return (dead);
// }

    // i = 0;
    // while (i < data.number_of_philosophers)
    // {
    //     ft_phil_init(&phil[i], &data, i);
    //     if (pthread_mutex_init(&mforks[i], NULL) != 0)
    //         return (write(2, "Mutex init fail!\n", 17));
    //     usleep (i % 2 * data.time_to_eat);
    //     if (pthread_create(&threads[i], NULL, &ft_phil_routine, &phil[i]) != 0)
    //     {
    //         perror("thread creation fails!\n");
    //         return (1);
    //     }
    //     i++;
    // }