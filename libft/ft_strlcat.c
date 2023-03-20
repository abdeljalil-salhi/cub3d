/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 15:51:46 by absalhi           #+#    #+#             */
/*   Updated: 2022/10/05 16:01:41 by absalhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	dsize;
	size_t	ssize;
	size_t	res;

	dsize = ft_strlen(dst);
	ssize = ft_strlen(src);
	if (dsize < dstsize)
		res = ssize + dsize;
	else
		res = ssize + dstsize;
	if (!dstsize)
		return (res);
	i = 0;
	while ((dsize + i < dstsize - 1) && src[i])
	{
		dst[dsize + i] = src[i];
		i++;
	}
	dst[dsize + i] = '\0';
	return (res);
}
