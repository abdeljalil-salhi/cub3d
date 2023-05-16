/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 08:43:52 by absalhi           #+#    #+#             */
/*   Updated: 2023/05/16 09:45:23 by absalhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	show_message(t_game *g, char *message)
{
	static int	frames = 0;
	
	if (frames > 10)
	{
		g->tips.open_door = !g->tips.open_door;
		frames = 0;
	}
	if (g->tips.open_door)
	{
		// t_iterators pos = {WIN_WIDTH / 2 - ft_strlen(message) * 6, WIN_HEIGHT - 20};

		// draw_rect(g, pos, ft_strlen(message) * 6, 20, create_trgb(80, 255, 0, 0));
		mlx_string_put(g->mlx, g->win.ref, WIN_WIDTH / 2 - ft_strlen(message) * 3, WIN_HEIGHT - 15, 0xFFFFFF, message);
	}
	frames++;
}

void	check_for_doors(t_game *g, int z)
{
	float	distance;

	distance = hypot(g->player.pos.x - g->objects[z].pos.x, g->player.pos.y - g->objects[z].pos.y);
	if (g->objects[z].state == DOOR_CLOSED)
	{
		if (distance < 200.0f)
		{
			show_message(g, "Press E to open the door");
			if (g->player.opening_door)
			{
				g->objects[z].state = DOOR_OPENED;
				g->map.arr[g->objects[z].y][g->objects[z].x] = DOOR_OPENED;
			}
		}
	}
	else if (g->objects[z].state == DOOR_OPENED)
	{
		if (distance > 200.0f)
		{
			g->objects[z].state = DOOR_CLOSED;
			g->map.arr[g->objects[z].y][g->objects[z].x] = DOOR_CLOSED;
		}
	}
}
