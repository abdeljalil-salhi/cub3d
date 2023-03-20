/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printchar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 22:12:25 by absalhi           #+#    #+#             */
/*   Updated: 2022/12/13 20:15:17 by absalhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printchar_no_option(char c)
{
	ft_putchar_fd(c, 1);
	return (1);
}

int	ft_printchar(char c, t_option option)
{
	int	res;

	res = 0;
	if (option.width > 1 && option.justify == '0')
		res += ft_putset('0', option.width - 1);
	else if (option.width > 1 && option.justify != '-')
		res += ft_putset(' ', option.width - 1);
	res += ft_printchar_no_option(c);
	if (option.width > 1 && option.justify == '-')
		res += ft_putset(' ', option.width - 1);
	return (res);
}
