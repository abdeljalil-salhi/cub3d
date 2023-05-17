/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   medkit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 06:20:43 by absalhi           #+#    #+#             */
/*   Updated: 2023/05/17 01:37:26 by absalhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	display_medkit_splash(t_game *g)
{
	static int	frames = 0;

	if (frames > 5)
	{
		g->player.taking_medkit = false;
		frames = 0;
	}
	frames++;
}

bool	check_for_medkits(t_game *g, int z)
{
	float	distance;

	if (g->objects[z].display)
	{
		distance = sqrt(pow(g->player.pos.x - g->objects[z].pos.x, 2) + pow(g->player.pos.y - g->objects[z].pos.y, 2));
		if (distance < 50.0f && g->player.health < 100)
		{
			g->player.taking_medkit = true;
			g->player.health += MEDKIT_HEALING;
			g->objects[z].display = false;
			return (false);
		}
		return (true);
	}
	return (false);
}
