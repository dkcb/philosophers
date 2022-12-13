/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   end.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkocob <dkocob@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/13 16:24:21 by dkocob        #+#    #+#                 */
/*   Updated: 2022/12/13 17:59:35 by dkocob        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

int cleaning(struct s_data *data)
{
    int i;
    
    i = 0;
    while (i < data->number_of_philosophers)
    {
        if (pthread_join(data->threads[i], NULL))
        {
            perror("thread join fails!\n");
            return (2);
        }
        // printf("thread joined\n");
        i++;
    }
    i = 0;
    while (i < data->number_of_philosophers)
    {
        pthread_mutex_destroy(&data->mforks[i]);
        i++;
    }
    return (0);
}