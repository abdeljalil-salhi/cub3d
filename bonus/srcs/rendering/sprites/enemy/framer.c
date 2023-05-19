/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   framer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 08:50:07 by absalhi           #+#    #+#             */
/*   Updated: 2023/05/19 09:03:44 by absalhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	frame_enemy_walk(t_game *g, int z)
{
	if (is_enemy_attacking(g->objects[z].type))
		g->objects[z].type -= 2;
	else
		g->objects[z].type--;
	g->objects[z].state = ENEMY_WALK;
	g->objects[z].frame = 0;
}

/*
**	Wait for 5 frames before changing the enemy's frame to give the impression
**	of a more realistic enemy.
*/

void	frame_enemy_damaged(t_game *g, int z)
{
	static int	frames = 0;

	frames++;
	if (frames > 5)
	{
		if (!is_enemy_damaged(g->objects[z].type))
			play_sound_effect(g, SOUND_NPC_DAMAGED);
		if (is_enemy_walking(g->objects[z].type))
			g->objects[z].type++;
		else if (is_enemy_attacking(g->objects[z].type))
			g->objects[z].type--;
		g->objects[z].frame = 0;
		frames = 0;
	}
}

static void	enemy_decision_randomizer(t_game *g, int z)
{
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
}

void	frame_enemy_attack(t_game *g, int z)
{
	static int	frames = 0;

	if (is_enemy_walking(g->objects[z].type))
		g->objects[z].type += 2;
	else if (is_enemy_damaged(g->objects[z].type))
		g->objects[z].type++;
	g->objects[z].state = ENEMY_ATTACK;
	g->objects[z].frame = 0;
	frames++;
	if (frames > 5)
	{
		play_sound_effect(g, SOUND_NPC_ATTACK);
		enemy_decision_randomizer(g, z);
		frames = 0;
	}
}

void	frame_enemy_death(t_game *g, int z)
{
	static int	frames = 0;

	frames++;
	if (frames > 5)
	{
		play_sound_effect(g, SOUND_NPC_DEATH);
		if (is_enemy_walking(g->objects[z].type))
			g->objects[z].type += 3;
		else if (is_enemy_damaged(g->objects[z].type))
			g->objects[z].type += 2;
		else if (is_enemy_attacking(g->objects[z].type))
			g->objects[z].type++;
		g->objects[z].frame = 0;
		frames = 0;
	}
}
