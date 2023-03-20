/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printstr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 22:13:17 by absalhi           #+#    #+#             */
/*   Updated: 2022/12/13 20:15:01 by absalhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printstr_no_option(char *s)
{
	ft_putstr_fd(s, 1);
	return (ft_strlen(s));
}

int	ft_printstr(char *s, t_option option)
{
	int		res;
	int		allocated;

	res = 0;
	allocated = 0;
	if (!s)
	{
		s = ft_calloc(7, sizeof(char));
		allocated = 1;
		ft_strlcpy(s, "(null)", 7);
	}
	if (option.precision < 0 || option.precision > (int) ft_strlen(s))
		option.precision = ft_strlen(s);
	if (option.justify == '0' && option.width > option.precision && !option.dot)
		res += ft_putset('0', option.width - option.precision);
	else if (option.justify != '-' && option.width > option.precision)
		res += ft_putset(' ', option.width - option.precision);
	res += write(1, s, option.precision);
	if (option.justify == '-' && option.width > option.precision)
		res += ft_putset(' ', option.width - res);
	if (allocated)
		free(s);
	return (res);
}
