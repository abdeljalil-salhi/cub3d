/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard_hooks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 15:32:28 by absalhi           #+#    #+#             */
/*   Updated: 2023/05/18 05:22:33 by absalhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	hook_key_press(int keycode, t_game *g)
{
	if (keycode == ESC)
		free_memory(g);
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
	return (RETURN_SUCCESS);
}

int	hook_key_release(int keycode, t_game *g)
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
	return (RETURN_SUCCESS);
}
