/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 03:20:03 by absalhi           #+#    #+#             */
/*   Updated: 2023/05/17 07:27:30 by absalhi          ###   ########.fr       */
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

bool	is_enemy_dead(int type)
{
	return (type == OBJECT_SOLDIER_DEATH);
}

void	check_for_enemies(t_game *g, int z)
{
	float		distance;
	static int	bullet_frames = 0;

	if (!is_enemy_dead(g->objects[z].type))
	{
		distance = hypot(g->player.pos.x - g->objects[z].pos.x, g->player.pos.y - g->objects[z].pos.y);
		if (g->objects[z].state == ENEMY_DAMAGED && g->player.shooting)
		{
			bullet_frames++;
			if (bullet_frames > 5)
			{
				g->objects[z].type = OBJECT_SOLDIER_DAMAGED;
				g->objects[z].frame = 0;
				bullet_frames = 0;
			}
		}
		else if (g->objects[z].state == ENEMY_DEATH)
		{
			bullet_frames++;
			if (bullet_frames > 5)
			{
				g->objects[z].type = OBJECT_SOLDIER_DEATH;
				g->objects[z].frame = 0;
				bullet_frames = 0;
			}
		}
		else if (!g->player.shooting)
		{
			if (distance < 200.0f)
			{
				g->objects[z].type = OBJECT_SOLDIER_ATTACK;
				g->objects[z].state = ENEMY_ATTACK;
				g->objects[z].frame = 0;
				if (rand() % 100 < g->objects[z].infos[ENEMY_PRECISION])
				{
					g->player.health -= g->objects[z].infos[ENEMY_DAMAGE];
					g->player.taking_damage = true;
				}
			}
			else if (g->objects[z].type == OBJECT_SOLDIER_ATTACK || g->objects[z].type == OBJECT_SOLDIER_DAMAGED)
			{
				g->objects[z].type = OBJECT_SOLDIER_WALK;
				g->objects[z].state = ENEMY_WALK;
				g->objects[z].frame = 0;
			}
		}
	}
}