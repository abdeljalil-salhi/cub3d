/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_keys.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 15:32:28 by absalhi           #+#    #+#             */
/*   Updated: 2023/05/18 00:21:19 by absalhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	cub_key_hook(int keycode, t_game *g)
{
	if (keycode == ESC)
		cub_free_memory(g);
	if (keycode == KEY_W && !g->paused)
		g->player.walk_direction = -1;
	else if (keycode == KEY_S && !g->paused)
		g->player.walk_direction = 1;
	else if (keycode == KEY_A && !g->paused)
		g->player.turn_direction = -1;
	else if (keycode == KEY_D && !g->paused)
		g->player.turn_direction = 1;
	else if (keycode == KEY_E && !g->paused)
		g->player.opening_door = true;
	else if (keycode == KEY_COMMAND)
		g->mouse.enabled = false;
	// else if (keycode == ARROW_LEFT)
	// 	g->player.rotation_direction = -1;
	// else if (keycode == ARROW_RIGHT)
	// 	g->player.rotation_direction = 1;
	return (RETURN_SUCCESS);
}

void	play_sound_effect(t_game *g, int sound);
void	switch_weapon(t_game *g, int type)
{
	if (type != g->textures.weapon.type && g->textures.weapon.collected[type])
	{
		if (type == WEAPON_KNIFE)
			play_sound_effect(g, SOUND_KNIFE_SWITCH);
		else if (type == WEAPON_SHOTGUN)
			play_sound_effect(g, SOUND_SHOTGUN_SWITCH);
		g->player.switching_weapon = true;
		g->textures.weapon.type = type;
		g->textures.weapon.frame = 0;
	}
}

int	cub_key_release(int keycode, t_game *g)
{
	if (keycode == KEY_W)
		g->player.walk_direction = 0;
	else if (keycode == KEY_S)
		g->player.walk_direction = 0;
	else if (keycode == KEY_A)
		g->player.turn_direction = 0;
	else if (keycode == KEY_D)
		g->player.turn_direction = 0;
	else if (keycode == KEY_E)
		g->player.opening_door = false;
	else if (keycode == KEY_M && !g->paused)
		g->display_map = !g->display_map;
	else if (keycode == KEY_P && !g->game_over)
		g->paused = !g->paused;
	else if (keycode == KEY_COMMAND)
		g->mouse.enabled = true;
	else if (keycode == KEY_1 && !g->paused && !g->player.switching_weapon)
		switch_weapon(g, WEAPON_KNIFE);
	else if (keycode == KEY_2 && !g->paused && !g->player.switching_weapon)
		switch_weapon(g, WEAPON_SHOTGUN);
	// else if (keycode == ARROW_LEFT)
	// 	g->player.rotation_direction = 0;
	// else if (keycode == ARROW_RIGHT)
	// 	g->player.rotation_direction = 0;
	return (RETURN_SUCCESS);
}
