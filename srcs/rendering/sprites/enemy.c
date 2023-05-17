/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 03:20:03 by absalhi           #+#    #+#             */
/*   Updated: 2023/05/17 22:01:01 by absalhi          ###   ########.fr       */
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

bool	is_enemy_walking(int type)
{
	return (type == OBJECT_SOLDIER_WALK || type == OBJECT_CYBERDEMON_WALK);
}

bool	is_enemy_attacking(int type)
{
	return (type == OBJECT_SOLDIER_ATTACK || type == OBJECT_CYBERDEMON_ATTACK);
}

bool	is_enemy_damaged(int type)
{
	return (type == OBJECT_SOLDIER_DAMAGED || type == OBJECT_CYBERDEMON_DAMAGED);
}

bool	is_enemy_dead(int type)
{
	return (type == OBJECT_SOLDIER_DEATH || type == OBJECT_CYBERDEMON_DEATH);
}

bool	has_wall_at(t_game *g, float x, float y);
void    enemy_movement(t_game *g, int z)
{
    t_coords	player_dir;
    float		normalize_magn;

    player_dir.x = g->player.pos.x - g->objects[z].pos.x;
    player_dir.y = g->player.pos.y - g->objects[z].pos.y;

    normalize_magn = hypot(player_dir.x, player_dir.y);
    player_dir.x /= normalize_magn;
    player_dir.y /= normalize_magn;

	if (!has_wall_at(g, g->objects[z].pos.x + g->objects[z].infos[ENEMY_SPEED] * player_dir.x * g->delta_time, g->objects[z].pos.y))
		g->objects[z].pos.x += g->objects[z].infos[ENEMY_SPEED] * player_dir.x * g->delta_time;
	if (!has_wall_at(g, g->objects[z].pos.x , g->objects[z].pos.y + g->objects[z].infos[ENEMY_SPEED] * player_dir.y * g->delta_time))
		g->objects[z].pos.y += g->objects[z].infos[ENEMY_SPEED] * player_dir.y * g->delta_time;
}

void	play_sound_effect(t_game *g, int sound);
void	check_for_enemies(t_game *g, int z)
{
	float		distance;
	static int	bullet_frames = 0;
	static int	attacking_frames = 0;

	if (!is_enemy_dead(g->objects[z].type) && g->objects[z].visible && !g->paused && !g->game_over)
	{
		distance = hypot(g->player.pos.x - g->objects[z].pos.x, g->player.pos.y - g->objects[z].pos.y);
		if (g->objects[z].state == ENEMY_DAMAGED && g->player.shooting)
		{
			bullet_frames++;
			if (bullet_frames > 5)
			{
				if (!is_enemy_damaged(g->objects[z].type))
					play_sound_effect(g, SOUND_NPC_DAMAGED);
				if (is_enemy_walking(g->objects[z].type))
					g->objects[z].type++;
				else if (is_enemy_attacking(g->objects[z].type))
					g->objects[z].type--;
				g->objects[z].frame = 0;
				bullet_frames = 0;
			}
		}
		else if (g->objects[z].state == ENEMY_DEATH)
		{
			bullet_frames++;
			if (bullet_frames > 5)
			{
				play_sound_effect(g, SOUND_NPC_DEATH);
				if (is_enemy_walking(g->objects[z].type))
					g->objects[z].type += 3;
				else if (is_enemy_damaged(g->objects[z].type))
					g->objects[z].type += 2;
				else if (is_enemy_attacking(g->objects[z].type))
					g->objects[z].type++;
				g->objects[z].frame = 0;
				bullet_frames = 0;
			}
		}
		else if (!g->player.shooting)
		{
			if (distance < (float) g->objects[z].infos[ENEMY_RANGE])
			{
				if (is_enemy_walking(g->objects[z].type))
					g->objects[z].type += 2;
				else if (is_enemy_damaged(g->objects[z].type))
					g->objects[z].type++;
				g->objects[z].state = ENEMY_ATTACK;
				g->objects[z].frame = 0;
				attacking_frames++;
				if (attacking_frames > 5)
				{
					play_sound_effect(g, SOUND_NPC_ATTACK);
					if (rand() % 100 < g->objects[z].infos[ENEMY_PRECISION])
					{
						play_sound_effect(g, SOUND_PLAYER_DAMAGED);
						g->player.health -= g->objects[z].infos[ENEMY_DAMAGE];
						g->player.taking_damage = true;
						if (g->player.health <= 0)
						{
							g->player.health = 0;
							g->paused = true;
							g->game_over = true;
						}
					}
					attacking_frames = 0;
				}
			}
			else if (is_enemy_attacking(g->objects[z].type) || is_enemy_damaged(g->objects[z].type))
			{
				if (is_enemy_attacking(g->objects[z].type))
					g->objects[z].type -= 2;
				else
					g->objects[z].type--;
				g->objects[z].state = ENEMY_WALK;
				g->objects[z].frame = 0;
			}
			if (distance > (float) g->objects[z].infos[ENEMY_RANGE])
				enemy_movement(g, z);
		}
	}
}
