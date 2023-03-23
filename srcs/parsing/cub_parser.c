/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 23:03:36 by absalhi           #+#    #+#             */
/*   Updated: 2023/03/23 23:08:00 by absalhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	cub_init_game_struct(t_game *g, char *filename)
{
	g->map.file.path = filename;
	g->parsing.is_map = false;
	g->parsing.map_initialized = false;
	g->parsing.has_north = false;
	g->parsing.has_south = false;
	g->parsing.has_west = false;
	g->parsing.has_east = false;
	g->parsing.has_floor = false;
	g->parsing.has_ceiling = false;
	g->paused = false;
	g->freeze = false;
	g->game_over = false;
}

int	cub_parser(t_game *g, char *filename)
{
	cub_init_game_struct(g, filename);
	if (cub_file_parser(g))
		return (RETURN_FAILURE);
	if (close(g->map.file.fd) == -1)
		return (cub_errors_setter(g, "Failed to close config file"));
	if (cub_check_map(g))
		return (RETURN_FAILURE);
	if (cub_check_occurences(g))
		return (RETURN_FAILURE);
	return (RETURN_SUCCESS);
}
