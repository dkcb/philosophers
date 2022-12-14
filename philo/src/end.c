/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   end.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkocob <dkocob@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/14 21:24:04 by dkocob        #+#    #+#                 */
/*   Updated: 2022/12/14 21:54:28 by dkocob        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

int	cleaning(struct s_data *d)
{
	int	i;

	i = 0;
	while (i < d->p_qty)
	{
		if (pthread_join(d->tarr[i], NULL))
		{
			perror("thread join fails!\n");
			return (2);
		}
		i++;
	}
	i = 0;
	while (i < d->p_qty)
	{
		pthread_mutex_destroy(&d->mforks[i]);
		i++;
	}
	return (0);
}
