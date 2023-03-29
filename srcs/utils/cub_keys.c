/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_keys.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 15:32:28 by absalhi           #+#    #+#             */
/*   Updated: 2023/03/29 03:55:04 by absalhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	cub_key_hook(int keycode, t_game *g)
{
	if (keycode == ESC)
		cub_free_memory(g);
	if (keycode == KEY_W)
		g->player.walk_direction = -1;
	else if (keycode == KEY_S)
		g->player.walk_direction = 1;
	else if (keycode == KEY_A)
		g->player.turn_direction = -1;
	else if (keycode == KEY_D)
		g->player.turn_direction = 1;
	else if (keycode == ARROW_LEFT)
		g->player.rotation_direction = -1;
	else if (keycode == ARROW_RIGHT)
		g->player.rotation_direction = 1;
	return (RETURN_SUCCESS);
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
	else if (keycode == ARROW_LEFT)
		g->player.rotation_direction = 0;
	else if (keycode == ARROW_RIGHT)
		g->player.rotation_direction = 0;
	return (RETURN_SUCCESS);
}
