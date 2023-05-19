/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 08:43:52 by absalhi           #+#    #+#             */
/*   Updated: 2023/05/19 01:43:28 by absalhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	animating_door_closed(t_game *g, int z)
{
	t_iterators	it;

	if (g->objects[z].frame < g->textures.object_n_of_frames[OBJECT_DOOR] - 1)
	{
		g->objects[z].frame++;
		g->objects[z].last_time = current_time_ms();
	}
	else
	{
		it.i = (int)g->objects[z].pos.x / TILE_SIZE;
		it.j = (int)g->objects[z].pos.y / TILE_SIZE;
		g->tips.open_door = false;
		g->objects[z].animating = false;
		g->objects[z].state = DOOR_OPENED;
		g->map.arr[it.j][it.i] = DOOR_OPENED;
	}
}

static void	animating_door_opened(t_game *g, int z)
{
	t_iterators	it;

	if (g->objects[z].frame > 0)
	{
		g->objects[z].frame--;
		g->objects[z].last_time = current_time_ms();
	}
	else
	{
		it.i = (int)g->objects[z].pos.x / TILE_SIZE;
		it.j = (int)g->objects[z].pos.y / TILE_SIZE;
		g->objects[z].animating = false;
		g->objects[z].state = DOOR_CLOSED;
		g->map.arr[it.j][it.i] = DOOR_CLOSED;
	}
}

static void	opening_door(t_game *g, int z)
{
	show_door_tip(g, z);
	if (g->player.opening_door && g->objects[z].frame == 0)
	{
		play_sound_effect(g, SOUND_DOOR_OPEN);
		g->objects[z].animating = true;
		g->objects[z].last_time = current_time_ms();
	}
}

static void	closing_door(t_game *g, int z)
{
	play_sound_effect(g, SOUND_DOOR_CLOSE);
	g->objects[z].animating = true;
	g->objects[z].last_time = current_time_ms();
	g->tips.open_door = false;
}

void	check_for_doors(t_game *g, int z)
{
	float	distance;

	distance = hypot(g->player.pos.x - g->objects[z].pos.x,
			g->player.pos.y - g->objects[z].pos.y);
	if (g->objects[z].state == DOOR_CLOSED)
	{
		if (g->objects[z].animating)
			animating_door_closed(g, z);
		else if (distance < 200.0f)
			opening_door(g, z);
	}
	else if (g->objects[z].state == DOOR_OPENED)
	{
		if (g->objects[z].animating)
			animating_door_opened(g, z);
		else if (distance > 200.0f && g->objects[z].frame
			== g->textures.object_n_of_frames[OBJECT_DOOR] - 1)
			closing_door(g, z);
	}
}
