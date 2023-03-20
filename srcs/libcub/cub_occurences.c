/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_occurences.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 23:30:40 by absalhi           #+#    #+#             */
/*   Updated: 2023/03/19 23:45:22 by absalhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	cub_count_occurences(char *str, char c)
{
	int	i;
	int	occur;

	i = -1;
	occur = 0;
	while (str[++i])
		if (str[i] == c)
			occur++;
	return (occur);
}
