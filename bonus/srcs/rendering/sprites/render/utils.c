/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 11:11:57 by absalhi           #+#    #+#             */
/*   Updated: 2023/05/19 11:12:14 by absalhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void compute_distances(t_game *g)
{
	int i;
	int x;
	int y;

	i = -1;
	while (++i < g->objects_count)
	{
		x = g->objects[i].pos.x - g->player.pos.x;
		y = g->objects[i].pos.y - g->player.pos.y;
		g->objects[i].dist = hypot(x, y);
	}
}
