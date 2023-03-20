/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printhex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 22:12:49 by absalhi           #+#    #+#             */
/*   Updated: 2022/12/13 20:15:22 by absalhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_hexlen(unsigned int n)
{
	size_t	len;

	len = 0;
	if (!n)
		return (1);
	while (n)
	{
		n /= 16;
		len++;
	}
	return (len);
}

static int	ft_printhex_formatcase(unsigned int n, t_option o, int l, int f)
{
	int	res;

	res = 0;
	if (o.prefix[1] == '#' && n)
	{
		if (f)
			res += ft_printstr_no_option("0X");
		else
			res += ft_printstr_no_option("0x");
	}
	if (o.precision > l && !o.justify)
		res += ft_putset('0', o.precision - l);
	if (o.width > l + res && o.justify == '0')
		res += ft_putset('0', o.width - l - res);
	ft_puthex_fd(n, 1, f);
	if (o.width > l - res && o.justify == '-')
		res += ft_putset(' ', o.width - l - res);
	return (res);
}

int	ft_printhex(unsigned int n, t_option option)
{
	int	res;
	int	len;

	len = ft_hexlen(n);
	res = ft_printhex_formatcase(n, option, len, option.format == 'X');
	return (res + len);
}
