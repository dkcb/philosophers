/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   death.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkocob <dkocob@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/14 21:23:51 by dkocob        #+#    #+#                 */
/*   Updated: 2022/12/14 21:23:58 by dkocob        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

int	death_check(struct s_data *data)
{
	pthread_mutex_lock(&data->mdeath);
	if (data->dead > 0)
	{
		pthread_mutex_unlock(&data->mdeath);
		return (1);
	}
	pthread_mutex_unlock(&data->mdeath);
	return (0);
}
