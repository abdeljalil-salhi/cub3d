/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 11:45:39 by absalhi           #+#    #+#             */
/*   Updated: 2023/05/19 11:45:40 by absalhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	find_hor_steps(t_game *g, int i, t_coords *dist, float *depth)
{
	if (g->rays[i].sin_a > 0)
	{
		g->rays[i].horz_inters.y = (g->player.map_pos.y + 1) * TILE_SIZE;
		dist->y = TILE_SIZE;
	}
	else
	{
		g->rays[i].horz_inters.y = g->player.map_pos.y * TILE_SIZE - 0.0001;
		dist->y = -TILE_SIZE;
	}
	g->rays[i].depth_horz = g->rays[i].horz_inters.y - g->player.pos.y;
	g->rays[i].depth_horz /= g->rays[i].sin_a;
	g->rays[i].horz_inters.x = g->rays[i].depth_horz * g->rays[i].cos_a;
	g->rays[i].horz_inters.x += g->player.pos.x;
	*depth = dist->y / g->rays[i].sin_a;
	dist->x = *depth * g->rays[i].cos_a;
}

void	find_vert_steps(t_game *g, int i, t_coords *dist, float *depth)
{
	if (g->rays[i].cos_a > 0)
	{
		g->rays[i].vert_inters.x = (g->player.map_pos.x + 1) * TILE_SIZE;
		dist->x = TILE_SIZE;
	}
	else
	{
		g->rays[i].vert_inters.x = g->player.map_pos.x * TILE_SIZE - 0.0001;
		dist->x = -TILE_SIZE;
	}
	g->rays[i].depth_vert = g->rays[i].vert_inters.x - g->player.pos.x;
	g->rays[i].depth_vert /= g->rays[i].cos_a;
	g->rays[i].vert_inters.y = g->rays[i].depth_vert * g->rays[i].sin_a;
	g->rays[i].vert_inters.y += g->player.pos.y;
	*depth = dist->x / g->rays[i].cos_a;
	dist->y = *depth * g->rays[i].sin_a;
}

void	check_horz_inters(t_game *g, int i, t_coords dist, float depth)
{
	t_iterators	horz_tile;
	int			j;

	j = 1;
	while (++j < MAX_DEPTH)
	{
		horz_tile.j = abs((int)(g->rays[i].horz_inters.x / TILE_SIZE));
		horz_tile.i = abs((int)(g->rays[i].horz_inters.y / TILE_SIZE));
		if (horz_tile.i >= g->map.height || horz_tile.j >= g->map.width)
			break ;
		if (check_if_wall(g->map.arr[horz_tile.i][horz_tile.j]))
		{
			g->rays[i].horz_wall_content = g->map.arr[horz_tile.i][horz_tile.j];
			break ;
		}
		g->rays[i].horz_inters.x += dist.x;
		g->rays[i].horz_inters.y += dist.y;
		g->rays[i].depth_horz += depth;
	}
}

void	check_vert_inters(t_game *g, int i, t_coords dist, float depth)
{
	t_iterators	vert_tile;
	int			j;

	j = -1;
	while (++j < MAX_DEPTH)
	{
		vert_tile.j = abs((int)(g->rays[i].vert_inters.x / TILE_SIZE));
		vert_tile.i = abs((int)(g->rays[i].vert_inters.y / TILE_SIZE));
		if (vert_tile.i >= g->map.height || vert_tile.j >= g->map.width)
			break ;
		if (check_if_wall(g->map.arr[vert_tile.i][vert_tile.j]))
		{
			g->rays[i].vert_wall_content = g->map.arr[vert_tile.i][vert_tile.j];
			break ;
		}
		g->rays[i].vert_inters.x += dist.x;
		g->rays[i].vert_inters.y += dist.y;
		g->rays[i].depth_vert += depth;
	}
}

void	final_inters(t_game *g, int i)
{
	if (g->rays[i].depth_vert < g->rays[i].depth_horz)
	{
		g->rays[i].vert_inters.y = fmod(g->rays[i].vert_inters.y, TILE_SIZE);
		g->rays[i].depth = g->rays[i].depth_vert;
		g->rays[i].wall_hit = g->rays[i].vert_inters;
		g->rays[i].content_hit = g->rays[i].vert_wall_content;
		g->rays[i].vertical_hit = true;
	}
	else
	{
		g->rays[i].horz_inters.x = fmod(g->rays[i].horz_inters.x, TILE_SIZE);
		g->rays[i].depth = g->rays[i].depth_horz;
		g->rays[i].wall_hit = g->rays[i].horz_inters;
		g->rays[i].content_hit = g->rays[i].horz_wall_content;
		g->rays[i].vertical_hit = false;
	}
}
