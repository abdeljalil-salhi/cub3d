/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 03:20:03 by absalhi           #+#    #+#             */
/*   Updated: 2023/05/20 02:06:15 by absalhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	check_if_enemy_damaged(t_game *g, int i)
{
	return (g->player.shooting && g->player.damaging
		&& hypot(g->objects[i].pos.x - g->player.pos.x,
			g->objects[i].pos.y - g->player.pos.y)
		<= g->textures.weapon.range[g->textures.weapon.type]);
}

void	check_if_enemy(t_game *g, int x, int y)
{
	int	i;

	i = -1;
	while (++i < g->objects_count)
	{
		if ((int)(g->objects[i].pos.x / TILE_SIZE) == x
			&& (int)(g->objects[i].pos.y / TILE_SIZE) == y)
		{
			g->objects[i].visible = true;
			if (is_enemy(g->objects[i].type) && check_if_enemy_damaged(g, i))
			{
				g->player.damaging = false;
				g->objects[i].state = ENEMY_DAMAGED;
				g->objects[i].infos[ENEMY_HEALTH]
					-= g->textures.weapon.damage[g->textures.weapon.type];
				if (g->objects[i].infos[ENEMY_HEALTH] <= 0
					&& !is_enemy_dead(g->objects[i].type))
				{
					g->objects[i].infos[ENEMY_HEALTH] = 0;
					g->objects[i].state = ENEMY_DEATH;
					g->player.score += g->objects[i].infos[ENEMY_BOUNTY];
				}
			}
		}
	}
}

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
