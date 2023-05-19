/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_occurences.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 23:30:40 by absalhi           #+#    #+#             */
/*   Updated: 2023/05/19 09:44:24 by absalhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	count_occurences(char *str, char c)
{
	int	i;
	int	occur;

	occur = 0;
	i = -1;
	while (str[++i])
		if (str[i] == c)
			occur++;
	return (occur);
}

int	count_int_occurences(int *arr, size_t size, int n)
{
	int	i;
	int	occur;

	occur = 0;
	i = -1;
	while ((size_t)++i < size)
		if (arr[i] == n)
			occur++;
	return (occur);
}
