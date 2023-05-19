/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_checker.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 03:52:45 by absalhi           #+#    #+#             */
/*   Updated: 2023/05/19 06:14:02 by absalhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	check_if_wall(int content)
{
	return (content == 1 || content == 2
		|| content == 3 || content == 4 || content == 5);
}

bool	has_wall_at(t_game *g, float x, float y)
{
	t_iterators	it;

	if (x < 0 || x > g->map.width * TILE_SIZE
		|| y < 0 || y > g->map.height * TILE_SIZE)
		return (true);
	it.i = (int)(x / TILE_SIZE);
	it.j = (int)(y / TILE_SIZE);
	return (check_if_wall(g->map.arr[it.j][it.i]));
}

bool	has_door_at(t_game *g, float x, float y)
{
	t_iterators	it;

	if (x < 0 || x > g->map.width * TILE_SIZE
		|| y < 0 || y > g->map.height * TILE_SIZE)
		return (false);
	it.i = (int)(x / TILE_SIZE);
	it.j = (int)(y / TILE_SIZE);
	return (g->map.arr[it.j][it.i] == DOOR_CLOSED);
}

void	check_wall_collision(t_game *g, float dx, float dy)
{
	int	scale;

	scale = PLAYER_SCALE;
	if (!has_wall_at(g, g->player.pos.x + dx * scale, g->player.pos.y)
		&& !has_door_at(g, g->player.pos.x + dx * scale, g->player.pos.y))
		g->player.pos.x += dx;
	if (!has_wall_at(g, g->player.pos.x, g->player.pos.y + dy * scale)
		&& !has_door_at(g, g->player.pos.x, g->player.pos.y + dy * scale))
		g->player.pos.y += dy;
}
