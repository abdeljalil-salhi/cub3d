/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tips.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 01:32:43 by absalhi           #+#    #+#             */
/*   Updated: 2023/05/19 01:33:53 by absalhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	show_door_tip(t_game *g, int z)
{
	static int	frames = 0;

	if (g->objects[z].visible)
	{
		if (frames > 10)
		{
			g->tips.open_door = !g->tips.open_door;
			frames = 0;
		}
		frames++;
	}
	else
	{
		g->tips.open_door = false;
		frames = 0;
	}
}

void	show_game_over_tip(t_game *g)
{
	static int	frames = 0;

	if (frames > 10)
	{
		g->tips.game_over = !g->tips.game_over;
		frames = 0;
	}
	frames++;
}
