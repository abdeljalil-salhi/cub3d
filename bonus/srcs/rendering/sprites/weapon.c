/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapon.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 05:52:12 by absalhi           #+#    #+#             */
/*   Updated: 2023/05/20 02:10:16 by absalhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	get_object_type(int z)
{
	if (z == OBJECT_WEAPON_SHOTGUN)
		return (WEAPON_SHOTGUN);
	return (0);
}

static void	animate_weapon(t_game *g, int type)
{
	t_ull	period;

	if (g->textures.weapon.frame == 0 && !g->textures.weapon.animating)
	{
		play_sound_effect(g, g->textures.weapon.sound[type]);
		g->player.damaging = true;
		g->textures.weapon.animating = true;
		g->textures.weapon.last_time = current_time_ms();
	}
	period = current_time_ms() - g->textures.weapon.last_time;
	if (period > g->textures.weapon.frame_rate[type])
	{
		g->textures.weapon.frame++;
		g->textures.weapon.last_time = current_time_ms();
	}
	if (g->textures.weapon.frame == g->textures.weapon.n_of_frames[type])
	{
		g->textures.weapon.animating = false;
		g->player.shooting = false;
		g->player.damaging = false;
		g->textures.weapon.frame = 0;
	}
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

void	draw_weapon(t_game *g)
{
	static int	switching_frames = 0;
	int	type;
	int	frame;

	type = g->textures.weapon.type;
	if (g->player.shooting)
		animate_weapon(g, type);
	if (g->player.switching_weapon)
	{
		switching_frames++;
		if (switching_frames > 5)
		{
			switching_frames = 0;
			g->player.switching_weapon = false;
		}
	}
	frame = g->textures.weapon.frame;
	mlx_put_image_to_window(g->mlx, g->win.ref,
		g->textures.weapon.image[type][frame].ref,
		g->textures.weapon.pos.x, g->textures.weapon.pos.y);
}
