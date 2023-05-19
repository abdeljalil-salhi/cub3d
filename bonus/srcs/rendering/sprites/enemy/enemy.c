/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 03:20:03 by absalhi           #+#    #+#             */
/*   Updated: 2023/05/19 09:31:28 by absalhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	display_enemy_splash(t_game *g)
{
	static int	frames = 0;

	if (frames > 5)
	{
		g->player.taking_damage = false;
		frames = 0;
	}
	frames++;
}

static bool	is_enemy_eligible(t_game *g, int z)
{
	return (
		!is_enemy_dead(g->objects[z].type)
		&& g->objects[z].visible && !g->paused
		&& !g->game_over
	);
}

void	check_for_enemies(t_game *g, int z)
{
	float	distance;
	float	distance_x;
	float	distance_y;

	if (is_enemy_eligible(g, z))
	{
		distance_x = g->player.pos.x - g->objects[z].pos.x;
		distance_y = g->player.pos.y - g->objects[z].pos.y;
		distance = hypot(distance_x, distance_y);
		if (g->objects[z].state == ENEMY_DAMAGED && g->player.shooting)
			frame_enemy_damaged(g, z);
		else if (g->objects[z].state == ENEMY_DEATH)
			frame_enemy_death(g, z);
		else if (!g->player.shooting)
		{
			if (distance < (float) g->objects[z].infos[ENEMY_RANGE])
				frame_enemy_attack(g, z);
			else if (is_enemy_attacking(g->objects[z].type)
				|| is_enemy_damaged(g->objects[z].type))
				frame_enemy_walk(g, z);
		}
		if (distance > (float) g->objects[z].infos[ENEMY_RANGE])
			enemy_movement(g, z);
	}
}
