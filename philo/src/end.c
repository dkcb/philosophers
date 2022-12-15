/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   end.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkocob <dkocob@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/14 21:24:04 by dkocob        #+#    #+#                 */
/*   Updated: 2022/12/15 18:35:47 by dkocob        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

int	cleaning(struct s_data *d, int i)
{
	while (i < d->p_tot)
	{
		if (pthread_join(d->tarr[i], NULL))
		{
			perror("thread join fails!\n");
		}
		i++;
	}
	if (pthread_join(d->tarr[200], NULL))
	{
		perror("thread join fails!\n");
	}
	i = 0;
	while (i < d->p_tot)
	{
		pthread_mutex_destroy(&d->mforks[i]);
		i++;
	}
	pthread_mutex_destroy(&d->mprint);
	pthread_mutex_destroy(&d->mdeath);
	return (0);
}
