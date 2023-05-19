/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 03:43:29 by absalhi           #+#    #+#             */
/*   Updated: 2023/05/19 08:46:02 by absalhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	check_enemy_x_axis(t_game *g, int z, t_coords player_dir, int speed)
{
	return ((
			has_wall_at(g,
				g->objects[z].pos.x + speed * player_dir.x * g->delta_time,
				g->objects[z].pos.y)
		) || (
			has_door_at(g,
				g->objects[z].pos.x + speed * player_dir.x * g->delta_time,
				g->objects[z].pos.y)
		));
}

static bool	check_enemy_y_axis(t_game *g, int z, t_coords player_dir, int speed)
{
	return ((
			has_wall_at(g,
				g->objects[z].pos.x,
				g->objects[z].pos.y + speed * player_dir.y * g->delta_time)
		) || (
			has_door_at(g,
				g->objects[z].pos.x,
				g->objects[z].pos.y + speed * player_dir.y * g->delta_time)
		));
}

void	enemy_movement(t_game *g, int z)
{
	int			speed;
	float		normalize;
	t_coords	player_dir;

	player_dir.x = g->player.pos.x - g->objects[z].pos.x;
	player_dir.y = g->player.pos.y - g->objects[z].pos.y;
	normalize = hypot(player_dir.x, player_dir.y);
	player_dir.x /= normalize;
	player_dir.y /= normalize;
	speed = g->objects[z].infos[ENEMY_SPEED];
	if (!check_enemy_x_axis(g, z, player_dir, speed))
		g->objects[z].pos.x += speed * player_dir.x * g->delta_time;
	if (!check_enemy_y_axis(g, z, player_dir, speed))
		g->objects[z].pos.y += speed * player_dir.y * g->delta_time;
}
