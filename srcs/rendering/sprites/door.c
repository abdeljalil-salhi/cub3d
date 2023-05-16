/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 08:43:52 by absalhi           #+#    #+#             */
/*   Updated: 2023/05/16 23:51:08 by absalhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	show_message(t_game *g)
{
	static int	frames = 0;
	
	if (frames > 10)
	{
		g->tips.open_door = !g->tips.open_door;
		frames = 0;
	}
	frames++;
}

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
				g->objects[z].animating = false;
				g->objects[z].state = DOOR_OPENED;
				g->map.arr[g->objects[z].y][g->objects[z].x] = DOOR_OPENED;
			}
		}
		else if (distance < 200.0f)
		{
			show_message(g);
			if (g->player.opening_door && g->objects[z].frame == 0)
			{
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
				g->map.arr[g->objects[z].y][g->objects[z].x] = DOOR_CLOSED;
			}
		}
		else if (distance > 200.0f && g->objects[z].frame == g->textures.object_n_of_frames[OBJECT_DOOR] - 1)
		{
			g->objects[z].animating = true;
			g->objects[z].last_time = current_time_ms();
		}
	}
}
