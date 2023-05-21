/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 08:34:35 by absalhi           #+#    #+#             */
/*   Updated: 2023/05/21 00:05:21 by absalhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_basic_objects(t_game *g)
{
	g->textures.object_path[OBJECT_BARREL][0] = BARREL;
	g->textures.object_n_of_frames[OBJECT_BARREL] = 1;
	g->textures.object_frame_rate[OBJECT_BARREL] = 0;
	g->textures.object_scale[OBJECT_BARREL] = 0.9;
	g->textures.object_path[OBJECT_PILLAR][0] = PILLAR;
	g->textures.object_n_of_frames[OBJECT_PILLAR] = 1;
	g->textures.object_frame_rate[OBJECT_PILLAR] = 0;
	g->textures.object_scale[OBJECT_PILLAR] = 1;
	g->textures.object_path[OBJECT_LAMP][0] = LAMP;
	g->textures.object_n_of_frames[OBJECT_LAMP] = 1;
	g->textures.object_frame_rate[OBJECT_LAMP] = 0;
	g->textures.object_scale[OBJECT_LAMP] = 1;
	g->textures.object_path[OBJECT_GREEN_LIGHT][0] = GREEN_LIGHT_0;
	g->textures.object_path[OBJECT_GREEN_LIGHT][1] = GREEN_LIGHT_1;
	g->textures.object_path[OBJECT_GREEN_LIGHT][2] = GREEN_LIGHT_2;
	g->textures.object_path[OBJECT_GREEN_LIGHT][3] = GREEN_LIGHT_3;
	g->textures.object_n_of_frames[OBJECT_GREEN_LIGHT] = 4;
	g->textures.object_frame_rate[OBJECT_GREEN_LIGHT] = 200;
	g->textures.object_scale[OBJECT_GREEN_LIGHT] = 1;
}

static void	init_interactive_objects(t_game *g)
{
	g->textures.object_path[OBJECT_DOOR][0] = DOOR_0;
	g->textures.object_path[OBJECT_DOOR][1] = DOOR_1;
	g->textures.object_path[OBJECT_DOOR][2] = DOOR_2;
	g->textures.object_path[OBJECT_DOOR][3] = DOOR_3;
	g->textures.object_n_of_frames[OBJECT_DOOR] = 4;
	g->textures.object_frame_rate[OBJECT_DOOR] = 200;
	g->textures.object_scale[OBJECT_DOOR] = 1;
	g->textures.object_path[OBJECT_MEDKIT][0] = MEDKIT;
	g->textures.object_n_of_frames[OBJECT_MEDKIT] = 1;
	g->textures.object_frame_rate[OBJECT_MEDKIT] = 0;
	g->textures.object_scale[OBJECT_MEDKIT] = 1;
	g->textures.object_path[OBJECT_WEAPON_SHOTGUN][0] = SHOTGUN_DROP_0;
	g->textures.object_path[OBJECT_WEAPON_SHOTGUN][1] = SHOTGUN_DROP_1;
	g->textures.object_path[OBJECT_WEAPON_SHOTGUN][2] = SHOTGUN_DROP_2;
	g->textures.object_path[OBJECT_WEAPON_SHOTGUN][3] = SHOTGUN_DROP_3;
	g->textures.object_path[OBJECT_WEAPON_SHOTGUN][4] = SHOTGUN_DROP_4;
	g->textures.object_path[OBJECT_WEAPON_SHOTGUN][5] = SHOTGUN_DROP_5;
	g->textures.object_n_of_frames[OBJECT_WEAPON_SHOTGUN] = 6;
	g->textures.object_frame_rate[OBJECT_WEAPON_SHOTGUN] = 200;
	g->textures.object_scale[OBJECT_WEAPON_SHOTGUN] = 0.8;
}

static int	open_objects_xpm_files(t_game *g, t_iterators it)
{
	g->textures.object_image[it.i][it.j].ref = mlx_xpm_file_to_image(g->mlx,
			g->textures.object_path[it.i][it.j],
			&g->textures.object_dimension[it.i].j,
			&g->textures.object_dimension[it.i].i);
	if (!g->textures.object_image[it.i][it.j].ref)
		return (errors_setter(g, FAIL_OBJECT_LOAD));
	g->textures.object_image[it.i][it.j].addr
		= mlx_get_data_addr(g->textures.object_image[it.i][it.j].ref,
			&g->textures.object_image[it.i][it.j].bpp,
			&g->textures.object_image[it.i][it.j].line_length,
			&g->textures.object_image[it.i][it.j].endian);
	if (!g->textures.object_image[it.i][it.j].addr)
		return (errors_setter(g, FAIL_OBJECT_DATA));
	return (RETURN_SUCCESS);
}

int	init_objects(t_game *g)
{
	t_iterators	it;

	init_basic_objects(g);
	init_interactive_objects(g);
	init_soldier(g);
	init_cyberdemon(g);
	init_cacodemon(g);
	it.i = -1;
	while (++it.i < N_OF_OBJECTS)
	{
		it.j = -1;
		while (++it.j < g->textures.object_n_of_frames[it.i])
			if (open_objects_xpm_files(g, it))
				return (RETURN_FAILURE);
	}
	return (RETURN_SUCCESS);
}
