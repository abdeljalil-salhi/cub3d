/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_occurences.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 23:30:40 by absalhi           #+#    #+#             */
/*   Updated: 2023/03/23 23:32:15 by absalhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	cub_count_occurences(char *str, char c)
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

int	cub_count_int_occurences(int *arr, size_t size, int n)
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
