/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 22:12:37 by absalhi           #+#    #+#             */
/*   Updated: 2022/12/13 20:14:51 by absalhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf(const char *s, ...)
{
	va_list	opts;
	int		res;

	if (!s)
		return (0);
	va_start(opts, s);
	res = ft_vprintf(s, opts);
	va_end(opts);
	return (res);
}

int	ft_vprintf(const char *s, va_list opts)
{
	t_option	option;
	int			res;
	int			i;

	if (!s)
		return (0);
	res = 0;
	i = -1;
	while (s[++i])
	{
		if (s[i] == 37 && s[i + 1])
		{
			option = ft_parse(&s[(i++) + 1]);
			i += option.step;
			res += ft_format(opts, option);
		}
		else
			res += ft_printchar_no_option(s[i]);
	}
	return (res);
}

int	ft_format(va_list opts, t_option option)
{
	int	res;

	res = 0;
	if (option.format == 'c')
		res += ft_printchar(va_arg(opts, int), option);
	else if (option.format == 's')
		res += ft_printstr(va_arg(opts, char *), option);
	else if (option.format == 'p')
		res += ft_printptr(va_arg(opts, unsigned long long), option);
	else if (option.format == 'd' || option.format == 'i')
		res += ft_printnbr(va_arg(opts, int), option);
	else if (option.format == 'u')
		res += ft_printunbr(va_arg(opts, int), option);
	else if (option.format == 'x' || option.format == 'X')
		res += ft_printhex(va_arg(opts, unsigned int), option);
	else if (option.format == '%')
		res += ft_printchar_no_option('%');
	return (res);
}
