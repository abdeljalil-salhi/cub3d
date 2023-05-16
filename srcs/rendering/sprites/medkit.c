/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   medkit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 06:20:43 by absalhi           #+#    #+#             */
/*   Updated: 2023/05/16 06:56:56 by absalhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	check_for_medkits(t_game *g, int z)
{
	float	distance;

	if (g->objects[z].display)
	{
		distance = sqrt(pow(g->player.pos.x - g->objects[z].pos.x, 2) + pow(g->player.pos.y - g->objects[z].pos.y, 2));
		if (distance < 50.0f && g->player.health < 100)
		{
			g->player.health += MEDKIT_HEALING;
			g->objects[z].display = false;
			return (false);
		}
		return (true);
	}
	return (false);
}
