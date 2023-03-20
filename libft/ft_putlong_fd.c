/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putlong_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 15:53:11 by absalhi           #+#    #+#             */
/*   Updated: 2022/10/22 16:32:04 by absalhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putlong_fd(long long n, int fd)
{
	if (n < 0)
	{
		ft_putchar_fd(45, fd);
		ft_putlong_fd(-n, fd);
	}
	else if (n >= 10)
	{
		ft_putlong_fd(n / 10, fd);
		ft_putchar_fd((n % 10) + 48, fd);
	}
	else
		ft_putchar_fd(n + 48, fd);
}
