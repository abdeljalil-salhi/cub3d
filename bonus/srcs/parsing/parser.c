/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 23:03:36 by absalhi           #+#    #+#             */
/*   Updated: 2023/05/19 10:29:48 by absalhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_global_struct(t_game *g, char *filename)
{
	g->win.width = WIN_WIDTH;
	g->win.height = WIN_HEIGHT;
	g->map.file.path = filename;
	g->parsing.is_map = false;
	g->parsing.map_initialized = false;
	g->rays = (t_ray *) malloc(NUM_RAYS * sizeof(t_ray));
	if (!g->rays)
		errors_exit(g, "Failed to allocate memory for rays");
}

int	config_parser(t_game *g, char *filename)
{
	init_global_struct(g, filename);
	if (file_parser(g))
		return (RETURN_FAILURE);
	if (close(g->map.file.fd) == -1)
		return (errors_setter(g, "Failed to close config file"));
	if (check_map_borders_and_components(g))
		return (RETURN_FAILURE);
	if (check_player_occurences(g))
		return (RETURN_FAILURE);
	return (RETURN_SUCCESS);
}
