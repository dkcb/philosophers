/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   death.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkocob <dkocob@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/14 21:23:51 by dkocob        #+#    #+#                 */
/*   Updated: 2022/12/14 21:50:53 by dkocob        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

int	death_check(struct s_data *d)
{
	pthread_mutex_lock(&d->mdeath);
	if (d->dead > 0)
	{
		pthread_mutex_unlock(&d->mdeath);
		return (1);
	}
	pthread_mutex_unlock(&d->mdeath);
	return (0);
}
