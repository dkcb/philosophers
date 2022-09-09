/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlcat.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkocob <dkocob@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/17 15:29:12 by dkocob        #+#    #+#                 */
/*   Updated: 2021/02/10 16:49:11 by dkocob        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	d;
	size_t	destlen;
	size_t	srclen;

	srclen = ft_strlen(src);
	destlen = ft_strlen(dst);
	d = destlen;
	i = 0;
	if (destlen == size)
		return (size + srclen);
	if (destlen < size - 1 && size > 0)
	{
		while (src[i] && destlen + i < size - 1)
		{
			dst[d] = src[i];
			d++;
			i++;
		}
		dst[d] = 0;
	}
	if (destlen >= size)
		destlen = size;
	return (destlen + srclen);
}
