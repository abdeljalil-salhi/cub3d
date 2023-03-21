/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 21:28:45 by absalhi           #+#    #+#             */
/*   Updated: 2023/03/21 00:18:57 by absalhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	cub_map_init(t_game *g, char *line)
{
	(void) g;
	(void) line;
	return (RETURN_SUCCESS);
}

int	cub_map_parse(t_game *g, char *line)
{
	(void) g;
	(void) line;
	return (RETURN_SUCCESS);
}

int	cub_map_check(t_game *g)
{
	if (g->parsing.has_north && g->parsing.has_south && g->parsing.has_west
		&& g->parsing.has_east && g->parsing.has_floor && g->parsing.has_ceiling)
		g->parsing.is_map = true;
	return (RETURN_SUCCESS);
}
