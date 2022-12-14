/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   end.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkocob <dkocob@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/14 21:24:04 by dkocob        #+#    #+#                 */
/*   Updated: 2022/12/14 21:24:06 by dkocob        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

int	cleaning(struct s_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		if (pthread_join(data->tarr[i], NULL))
		{
			perror("thread join fails!\n");
			return (2);
		}
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
