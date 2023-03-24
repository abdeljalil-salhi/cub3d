/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 00:18:54 by absalhi           #+#    #+#             */
/*   Updated: 2023/03/24 00:19:04 by absalhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	cub_line_empty(char *line)
{
	int	i;

	i = -1;
	while (line[++i] == 32 || (line[i] >= 9 && line[i] <= 13))
		;
	if (line[i] == '\0' || line[i] == '\n')
		return (true);
	return (false);
}
