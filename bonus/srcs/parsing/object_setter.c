/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_setter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 10:11:14 by absalhi           #+#    #+#             */
/*   Updated: 2023/05/19 10:18:28 by absalhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	static_objects_setter(t_game *g, char c, int count)
{
	if (c == 'B')
		g->objects[count].type = OBJECT_BARREL;
	else if (c == 'P')
		g->objects[count].type = OBJECT_PILLAR;
	else if (c == 'L')
		g->objects[count].type = OBJECT_LAMP;
	else if (c == 'G')
		g->objects[count].type = OBJECT_GREEN_LIGHT;
}

static void	interactive_objects_setter(t_game *g, char c, int count,
	t_iterators it)
{
	if (c == 'M')
		g->objects[count].type = OBJECT_MEDKIT;
	else if (c == 'D')
	{
		g->map.arr[it.i][it.j] = DOOR_CLOSED;
		g->objects[count].type = OBJECT_DOOR;
		g->objects[count].state = DOOR_CLOSED;
	}
	else if (c == 'H')
		g->objects[count].type = OBJECT_WEAPON_SHOTGUN;
}

static void	enemies_setter(t_game *g, char c, int count)
{
	if (c == 'V')
	{
		g->objects[count].type = OBJECT_SOLDIER_WALK;
		g->objects[count].infos[ENEMY_HEALTH] = 70;
		g->objects[count].infos[ENEMY_BOUNTY] = 150;
		g->objects[count].infos[ENEMY_PRECISION] = 40;
		g->objects[count].infos[ENEMY_DAMAGE] = 25;
		g->objects[count].infos[ENEMY_RANGE] = 300;
		g->objects[count].infos[ENEMY_SPEED] = 200;
	}
	else if (c == 'C')
	{
		g->objects[count].type = OBJECT_CYBERDEMON_WALK;
		g->objects[count].infos[ENEMY_HEALTH] = 200;
		g->objects[count].infos[ENEMY_BOUNTY] = 500;
		g->objects[count].infos[ENEMY_PRECISION] = 40;
		g->objects[count].infos[ENEMY_DAMAGE] = 40;
		g->objects[count].infos[ENEMY_RANGE] = 500;
		g->objects[count].infos[ENEMY_SPEED] = 70;
	}
}

bool	is_object(char c)
{
	return (c == 'B' || c == 'L' || c == 'P' || c == 'G'
		|| c == 'M' || c == 'D' || c == 'V' || c == 'C' || c == 'H');
}

void	object_setter(t_game *g, char c, int i, int j)
{
	static int	count = 0;

	g->map.arr[i][j] = 0;
	g->objects[count].state = 0;
	g->objects[count].infos[ENEMY_HEALTH] = 1;
	static_objects_setter(g, c, count);
	interactive_objects_setter(g, c, count, (t_iterators){i, j});
	enemies_setter(g, c, count);
	g->objects[count].pos.x = j * TILE_SIZE + TILE_SIZE / 2;
	g->objects[count].pos.y = i * TILE_SIZE + TILE_SIZE / 2;
	g->objects[count].frame = 0;
	g->objects[count].animating = false;
	g->objects[count].visible = false;
	g->objects[count].display = true;
	count++;
}
