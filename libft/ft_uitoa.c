/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uitoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 16:00:59 by absalhi           #+#    #+#             */
/*   Updated: 2022/10/22 16:25:10 by absalhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_unblen(unsigned int n)
{
	size_t	len;

	len = 0;
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_uitoa(unsigned int n)
{
	char	*tab;
	size_t	i;

	i = ft_unblen(n);
	tab = (char *) ft_calloc(i + 1, sizeof(char));
	if (!tab)
		return (NULL);
	while (n)
	{
		tab[(i--) - 1] = (n % 10) + 48;
		n /= 10;
	}
	return (tab);
}
