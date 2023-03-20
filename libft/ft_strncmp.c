/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 11:39:08 by absalhi           #+#    #+#             */
/*   Updated: 2022/10/07 12:53:59 by absalhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (n - i > 0 && s1[i] == s2[i] && s1[i])
		i++;
	if (!(n - i))
		return (0);
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
