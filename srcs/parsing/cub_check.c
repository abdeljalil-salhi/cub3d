/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 17:19:06 by absalhi           #+#    #+#             */
/*   Updated: 2023/03/23 18:13:16 by absalhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	cub_check_map(t_game *g)
{
	int	i;
	int	j;

	i = -1;
	while (++i < g->map.width)
		if (g->map.arr[0][i] == 0 || g->map.arr[g->map.height - 1][i] == 0)
			return (cub_errors_setter(g, MAP_INVALID_BORDER));
	i = -1;
	while (++i < g->map.height)
		if (g->map.arr[i][0] == 0 || g->map.arr[i][g->map.width - 1] == 0)
			return (cub_errors_setter(g, MAP_INVALID_BORDER));
	i = -1;
	while (++i < g->map.height)
	{
		j = -1;
		while (++j < g->map.width)
		{
			if (j + 1 < g->map.width && g->map.arr[i][j] == -1 && g->map.arr[i][j + 1] == 0)
				return (cub_errors_setter(g, MAP_INVALID_BORDER));
			if (i + 1 < g->map.height && g->map.arr[i][j] == -1 && g->map.arr[i + 1][j] == 0)
				return (cub_errors_setter(g, MAP_INVALID_BORDER));
			if (j + 1 < g->map.width && g->map.arr[i][j] == 0 && g->map.arr[i][j + 1] == -1)
				return (cub_errors_setter(g, MAP_INVALID_BORDER));
			if (i + 1 < g->map.height && g->map.arr[i][j] == 0 && g->map.arr[i + 1][j] == -1)
				return (cub_errors_setter(g, MAP_INVALID_BORDER));
		}
	}
	return (RETURN_SUCCESS);
}
