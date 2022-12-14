/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   libft.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkocob <dkocob@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/14 21:24:43 by dkocob        #+#    #+#                 */
/*   Updated: 2022/12/14 21:24:44 by dkocob        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

static int	ft_isspace(char c)
{
	if (c == '\t' || c == '\n' || c == '\v'
		|| c == '\f' || c == '\r' || c == ' ')
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	int		i;
	int		sign;
	long	res;

	sign = 1;
	i = 0;
	res = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = sign * -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = (res * 10) + (str[i] - '0');
		i++;
		if (res > 2147483647 && sign == 1)
			return (-1);
		if (res > 2147483648 && sign == -1)
			return (0);
	}
	return ((int)(res * sign));
}
