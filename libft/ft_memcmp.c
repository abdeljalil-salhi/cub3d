/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 20:59:25 by absalhi           #+#    #+#             */
/*   Updated: 2022/10/07 11:15:24 by absalhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*str1;
	unsigned char	*str2;
	signed int		i;

	str1 = (void *)s1;
	str2 = (void *)s2;
	i = -1;
	while ((size_t)++i < n)
		if (str1[i] != str2[i])
			return (str1[i] - str2[i]);
	return (0);
}
