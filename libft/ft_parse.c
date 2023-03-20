/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 22:17:28 by absalhi           #+#    #+#             */
/*   Updated: 2022/12/13 20:14:36 by absalhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_option	ft_parse(const char *s)
{
	t_option	option;
	int			i;
	int			width;
	int			precision;

	option.justify = 0;
	option.prefix[0] = 0;
	option.prefix[1] = 0;
	option.precision = -1;
	option.width = 0;
	option.format = 0;
	option.step = 0;
	option.dot = 0;
	i = 0;
	while (s[i] && (ft_justify(s[i], &option) || ft_prefix(s[i], &option)))
		i++;
	width = ft_width(&s[i], &option);
	if (s[i] && width)
		i += width;
	precision = ft_precision(&s[i], &option);
	if (s[i] && precision)
		i += precision;
	option.format = s[i];
	option.step = i;
	return (option);
}

int	ft_justify(const char c, t_option *option)
{
	if (c == '0' || c == '-')
	{
		if (c == '0' && option->justify == 0)
			option->justify = c;
		else
			option->justify = '-';
	}
	else
		return (0);
	return (1);
}

int	ft_prefix(const char c, t_option *option)
{
	if (c == '+' || c == ' ')
	{
		if (c == ' ' && option->prefix[0] == 0)
			option->prefix[0] = c;
		else
			option->prefix[0] = '+';
	}
	else if (c == '#')
		option->prefix[1] = '#';
	else
		return (0);
	return (1);
}

int	ft_width(const char *s, t_option *option)
{
	if (ft_isdigit(*s))
	{
		option->width = ft_atoi(s);
		return (ft_nblen(option->width));
	}
	return (0);
}

int	ft_precision(const char *s, t_option *option)
{
	if (s[0] == '.')
	{
		option->dot = 1;
		option->precision = ft_atoi(s + 1);
		if (option->precision != 0)
			return (ft_nblen(option->precision) + 1);
		return (1);
	}
	return (0);
}
