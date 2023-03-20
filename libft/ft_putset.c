/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 23:49:27 by absalhi           #+#    #+#             */
/*   Updated: 2022/10/21 23:49:40 by absalhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putset(char c, int len)
{
	int	i;

	if (len <= 0)
		return (0);
	i = -1;
	while (++i < len)
		ft_putchar_fd(c, 1);
	return (len);
}
