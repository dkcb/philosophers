/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putnbr_fd.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkocob <dkocob@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/17 15:29:12 by dkocob        #+#    #+#                 */
/*   Updated: 2021/02/10 16:49:06 by dkocob        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int i, int fd)
{
	char	c;

	if (i == -2147483648)
	{
		write(fd, "-2147483648", 11);
	}
	else
	{
		if (i < 0)
		{
			i = i * -1;
			write(fd, "-", 1);
		}
		if (i >= 10)
		{
			ft_putnbr_fd(i / 10, fd);
		}
		i = i % 10;
		c = i + 48;
		write(fd, &c, 1);
	}
}
