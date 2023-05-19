/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapon.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 00:50:12 by absalhi           #+#    #+#             */
/*   Updated: 2023/05/19 02:40:25 by absalhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_knife(t_game *g)
{
	g->textures.weapon.path[WEAPON_KNIFE][0] = KNIFE_0;
	g->textures.weapon.path[WEAPON_KNIFE][1] = KNIFE_1;
	g->textures.weapon.path[WEAPON_KNIFE][2] = KNIFE_2;
	g->textures.weapon.path[WEAPON_KNIFE][3] = KNIFE_3;
	g->textures.weapon.n_of_frames[WEAPON_KNIFE] = WEAPON_KNIFE_FRAMES;
	g->textures.weapon.frame_rate[WEAPON_KNIFE] = 80;
	g->textures.weapon.damage[WEAPON_KNIFE] = 50;
	g->textures.weapon.range[WEAPON_KNIFE] = 100.0f;
	g->textures.weapon.sound[WEAPON_KNIFE] = SOUND_KNIFE;
	g->textures.weapon.collected[WEAPON_KNIFE] = true;
}

static void	init_shotgun(t_game *g)
{
	g->textures.weapon.path[WEAPON_SHOTGUN][0] = SHOTGUN_0;
	g->textures.weapon.path[WEAPON_SHOTGUN][1] = SHOTGUN_1;
	g->textures.weapon.path[WEAPON_SHOTGUN][2] = SHOTGUN_2;
	g->textures.weapon.path[WEAPON_SHOTGUN][3] = SHOTGUN_3;
	g->textures.weapon.path[WEAPON_SHOTGUN][4] = SHOTGUN_4;
	g->textures.weapon.path[WEAPON_SHOTGUN][5] = SHOTGUN_5;
	g->textures.weapon.n_of_frames[WEAPON_SHOTGUN] = WEAPON_SHOTGUN_FRAMES;
	g->textures.weapon.frame_rate[WEAPON_SHOTGUN] = 80;
	g->textures.weapon.damage[WEAPON_SHOTGUN] = 30;
	g->textures.weapon.range[WEAPON_SHOTGUN] = 300.0f;
	g->textures.weapon.sound[WEAPON_SHOTGUN] = SOUND_SHOTGUN;
	g->textures.weapon.collected[WEAPON_SHOTGUN] = false;
}

static int	open_weapons_xpm_files(t_game *g, t_iterators it)
{
	g->textures.weapon.image[it.i][it.j].ref = mlx_xpm_file_to_image(g->mlx,
			g->textures.weapon.path[it.i][it.j],
			&g->textures.weapon.dimension[it.i].j,
			&g->textures.weapon.dimension[it.i].i);
	if (!g->textures.weapon.image[it.i][it.j].ref)
		return (errors_setter(g, FAIL_WEAPON_LOAD));
	g->textures.weapon.image[it.i][it.j].addr
		= mlx_get_data_addr(g->textures.weapon.image[it.i][it.j].ref,
			&g->textures.weapon.image[it.i][it.j].bpp,
			&g->textures.weapon.image[it.i][it.j].line_length,
			&g->textures.weapon.image[it.i][it.j].endian);
	if (!g->textures.weapon.image[it.i][it.j].addr)
		return (errors_setter(g, FAIL_WEAPON_DATA));
	return (RETURN_SUCCESS);
}

int	init_weapon(t_game *g)
{
	t_iterators	it;

	g->textures.weapon.type = WEAPON_KNIFE;
	g->textures.weapon.frame = 0;
	init_knife(g);
	init_shotgun(g);
	it.i = -1;
	while (++it.i < N_OF_WEAPONS)
	{
		it.j = -1;
		while (++it.j < g->textures.weapon.n_of_frames[it.i])
			if (open_weapons_xpm_files(g, it))
				return (RETURN_FAILURE);
	}
	g->textures.weapon.pos.x
		= HALF_WIN_WIDTH - g->textures.weapon.dimension[WEAPON_SHOTGUN].j / 2;
	g->textures.weapon.pos.y
		= WIN_HEIGHT - g->textures.weapon.dimension[WEAPON_SHOTGUN].i;
	return (RETURN_SUCCESS);
}
