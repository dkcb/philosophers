/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkocob <dkocob@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/17 15:29:12 by dkocob        #+#    #+#                 */
/*   Updated: 2022/06/18 15:54:24 by dkocob        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_lncnt(char const *s, char c)
{
	size_t	i;
	size_t	y;

	i = 0;
	y = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
		{
			i++;
		}
		if (s[i] && s[i] != c)
		{
			while (s[i] && s[i] != c)
				i++;
			y++;
		}
	}
	return (y);
}

static char	**ft_malloc_error(char **result)
{
	size_t	i;

	i = 0;
	while (result[i])
	{
		free(result[i]);
		i++;
	}
	free(result);
	return (NULL);
}

static char	**ft_malloc_array2(char const *s, char c, size_t x, size_t y)
{
	size_t	start_x;
	char	**result;

	result = (char **)malloc(sizeof(char *) * (ft_lncnt(s, c) + 1));
	if (result == NULL)
		return (NULL);
	while (y < ft_lncnt(s, c))
	{
		start_x = x;
		while (s[x] && s[x] == c)
		{
			x++;
			start_x = x;
		}
		while (s[x] && s[x] != c)
			x++;
		result[y] = (char *)malloc(sizeof(char) * ((x + 1 - start_x)));
		if (result[y] == NULL)
			return (ft_malloc_error(result));
		ft_strlcpy(result[y], s + start_x, x + 1 - start_x);
		y++;
	}
	result[y] = (NULL);
	return (result);
}

char	**ft_split(char const *s, char c)
{
	char	**result;

	if (!s)
		return (NULL);
	result = ft_malloc_array2(s, c, 0, 0);
	if (result == NULL)
		return (NULL);
	return (result);
}
