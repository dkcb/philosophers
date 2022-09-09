/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoa.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkocob <dkocob@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/17 15:29:12 by dkocob        #+#    #+#                 */
/*   Updated: 2022/06/18 15:52:33 by dkocob        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_cnt_len(int n)
{
	int	j;

	if (n == 0)
		return (1);
	j = 0;
	while (n >= 1)
	{
		n = n / 10;
		j++;
	}
	return (j);
}

static int	ft_cnt_apwr(int n)
{
	int	p;

	p = 1;
	while (n >= 10)
	{
		n = n / 10;
		p *= 10;
	}
	return (p);
}

static char	*ft_malloc_it(int n, int neg, int l)
{
	char	*str;

	if (n < 0)
	{
		n = n * -1;
		neg = 1;
	}
	l = ft_cnt_len(n);
	str = malloc(sizeof(char) * (l + neg + 1));
	if (!str)
		return (NULL);
	if (neg == 1)
		str[0] = '-';
	str[l + neg] = '\0';
	return (str);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		i;
	int		abspower;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	i = 0;
	str = ft_malloc_it(n, 0, 0);
	if (!str)
		return (NULL);
	if (n < 0)
	{
		n = n * -1;
		i++;
	}
	abspower = ft_cnt_apwr(n);
	while (abspower != 1)
	{
		str[i] = (n / abspower) + 48;
		n = n % abspower;
		abspower = abspower / 10;
		i++;
	}
	str[i] = n + 48;
	return (str);
}
