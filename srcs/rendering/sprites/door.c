/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 08:43:52 by absalhi           #+#    #+#             */
/*   Updated: 2023/05/17 11:40:31 by absalhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	show_door_tip(t_game *g)
{
	static int	frames = 0;

	if (frames > 10)
	{
		g->tips.open_door = !g->tips.open_door;
		frames = 0;
	}
	frames++;
}

void	play_sound_effect(t_game *g, int sound);
void	check_for_doors(t_game *g, int z)
{
	float	distance;

	distance = hypot(g->player.pos.x - g->objects[z].pos.x, g->player.pos.y - g->objects[z].pos.y);
	if (g->objects[z].state == DOOR_CLOSED)
	{
		if (g->objects[z].animating)
		{
			if (g->objects[z].frame < g->textures.object_n_of_frames[OBJECT_DOOR] - 1)
			{
				g->objects[z].frame++;
				g->objects[z].last_time = current_time_ms();
			}
			else
			{
				g->tips.open_door = false;
				g->objects[z].animating = false;
				g->objects[z].state = DOOR_OPENED;
				g->map.arr[(int)g->objects[z].pos.y / TILE_SIZE][(int)g->objects[z].pos.x / TILE_SIZE] = DOOR_OPENED;
			}
		}
		else if (distance < 200.0f)
		{
			show_door_tip(g);
			if (g->player.opening_door && g->objects[z].frame == 0)
			{
				play_sound_effect(g, SOUND_DOOR_OPEN);
				g->objects[z].animating = true;
				g->objects[z].last_time = current_time_ms();
			}
		}
	}
	else if (g->objects[z].state == DOOR_OPENED)
	{
		if (g->objects[z].animating)
		{
			if (g->objects[z].frame > 0)
			{
				g->objects[z].frame--;
				g->objects[z].last_time = current_time_ms();
			}
			else
			{
				g->objects[z].animating = false;
				g->objects[z].state = DOOR_CLOSED;
				g->map.arr[(int)g->objects[z].pos.y / TILE_SIZE][(int)g->objects[z].pos.x / TILE_SIZE] = DOOR_CLOSED;
			}
		}
		else if (distance > 200.0f && g->objects[z].frame == g->textures.object_n_of_frames[OBJECT_DOOR] - 1)
		{
			play_sound_effect(g, SOUND_DOOR_CLOSE);
			g->objects[z].animating = true;
			g->objects[z].last_time = current_time_ms();
		}
	}
}
