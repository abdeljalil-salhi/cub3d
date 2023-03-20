/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 16:46:45 by absalhi           #+#    #+#             */
/*   Updated: 2022/10/07 14:45:17 by absalhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*last;
	int		i;

	last = NULL;
	i = -1;
	while (s[++i])
		if (s[i] == (char) c)
			last = (char *) &s[i];
	if (s[i] == (char) c)
		return ((char *) &s[i]);
	return (last);
}
