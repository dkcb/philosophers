/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strnstr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkocob <dkocob@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/17 15:29:12 by dkocob        #+#    #+#                 */
/*   Updated: 2022/06/18 16:00:15 by dkocob        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s, const char *find, size_t slen)
{
	size_t	i;
	size_t	j;

	if (!s && !find)
		return (NULL);
	if (!find[0])
		return ((char *)s);
	i = 0;
	while (s[i] && i < slen)
	{
		j = 0;
		while (s[i + j] && find[j]
			&& i + j < slen && s[i + j] == find[j])
			j++;
		if (!find[j])
			return ((char *)(s + i));
		i++;
	}
	return (0);
}
