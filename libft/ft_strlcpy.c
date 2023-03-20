/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 15:10:29 by absalhi           #+#    #+#             */
/*   Updated: 2022/10/14 07:20:54 by absalhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	int	i;

	if (!dstsize)
		return (ft_strlen(src));
	i = -1;
	while (src[++i] && (size_t)i < (dstsize - 1))
		dst[i] = src[i];
	dst[i] = '\0';
	return (ft_strlen(src));
}
