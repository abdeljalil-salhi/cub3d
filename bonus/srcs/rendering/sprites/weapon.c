/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapon.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 05:52:12 by absalhi           #+#    #+#             */
/*   Updated: 2023/05/19 01:25:02 by absalhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	get_object_type(int z)
{
	if (z == OBJECT_WEAPON_SHOTGUN)
		return (WEAPON_SHOTGUN);
	return (0);
}

void	switch_weapon(t_game *g, int type)
{
	if (type != g->textures.weapon.type && g->textures.weapon.collected[type])
	{
		if (type == WEAPON_KNIFE)
			play_sound_effect(g, SOUND_KNIFE_SWITCH);
		else if (type == WEAPON_SHOTGUN)
			play_sound_effect(g, SOUND_SHOTGUN_SWITCH);
		g->player.switching_weapon = true;
		g->textures.weapon.type = type;
		g->textures.weapon.frame = 0;
	}
}

bool	check_for_weapon_drops(t_game *g, int z)
{
	float	distance;

	if (g->objects[z].display)
	{
		distance = hypot(g->player.pos.x - g->objects[z].pos.x,
				g->player.pos.y - g->objects[z].pos.y);
		if (distance < 50.0f)
		{
			g->textures.weapon.type = get_object_type(g->objects[z].type);
			if (g->textures.weapon.type == WEAPON_KNIFE)
				play_sound_effect(g, SOUND_KNIFE_SWITCH);
			else if (g->textures.weapon.type == WEAPON_SHOTGUN)
				play_sound_effect(g, SOUND_SHOTGUN_SWITCH);
			g->player.switching_weapon = true;
			g->objects[z].display = false;
			g->textures.weapon.collected[g->textures.weapon.type] = true;
			g->textures.weapon.frame = 0;
			return (false);
		}
		return (true);
	}
	return (false);
}
