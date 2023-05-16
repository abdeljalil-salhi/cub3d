/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 00:20:08 by absalhi           #+#    #+#             */
/*   Updated: 2023/05/16 06:20:09 by absalhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	cub_init_sprites(t_game *g)
{
	if (cub_init_weapon(g))
		return (RETURN_FAILURE);
	if (cub_init_objects(g))
		return (RETURN_FAILURE);
	return (RETURN_SUCCESS);
}

int	cub_init_textures(t_game *g)
{
	t_iterators	it;

	g->textures.sides[TEXTURE_NORTH].ref = mlx_xpm_file_to_image(g->mlx, g->assets.north, &it.i, &it.j);
	if (!g->textures.sides[TEXTURE_NORTH].ref)
		return (cub_errors_setter(g, "Failed to get data addr of north xpm."));
	g->textures.sides[TEXTURE_NORTH].addr = mlx_get_data_addr(g->textures.sides[TEXTURE_NORTH].ref,
			&g->textures.sides[TEXTURE_NORTH].bpp, &g->textures.sides[TEXTURE_NORTH].line_length, &g->textures.sides[TEXTURE_NORTH].endian);
	if (!g->textures.sides[TEXTURE_NORTH].addr)
		return (cub_errors_setter(g, "Failed to get data addr of north xpm."));
	g->textures.sides[TEXTURE_SOUTH].ref = mlx_xpm_file_to_image(g->mlx, g->assets.south, &it.i, &it.j);
	if (!g->textures.sides[TEXTURE_SOUTH].ref)
		return (cub_errors_setter(g, "Failed to get data addr of south xpm."));
	g->textures.sides[TEXTURE_SOUTH].addr = mlx_get_data_addr(g->textures.sides[TEXTURE_SOUTH].ref,
			&g->textures.sides[TEXTURE_SOUTH].bpp, &g->textures.sides[TEXTURE_SOUTH].line_length, &g->textures.sides[TEXTURE_SOUTH].endian);
	if (!g->textures.sides[TEXTURE_SOUTH].addr)
		return (cub_errors_setter(g, "Failed to get data addr of south xpm."));
	g->textures.sides[TEXTURE_EAST].ref = mlx_xpm_file_to_image(g->mlx, g->assets.east, &it.i, &it.j);
	if (!g->textures.sides[TEXTURE_EAST].ref)
		return (cub_errors_setter(g, "Failed to get data addr of east xpm."));
	g->textures.sides[TEXTURE_EAST].addr = mlx_get_data_addr(g->textures.sides[TEXTURE_EAST].ref,
			&g->textures.sides[TEXTURE_EAST].bpp, &g->textures.sides[TEXTURE_EAST].line_length, &g->textures.sides[TEXTURE_EAST].endian);
	if (!g->textures.sides[TEXTURE_EAST].addr)
		return (cub_errors_setter(g, "Failed to get data addr of east xpm."));
	g->textures.sides[TEXTURE_WEST].ref = mlx_xpm_file_to_image(g->mlx, g->assets.west, &it.i, &it.j);
	if (!g->textures.sides[TEXTURE_WEST].ref)
		return (cub_errors_setter(g, "Failed to get data addr of west xpm."));
	g->textures.sides[TEXTURE_WEST].addr = mlx_get_data_addr(g->textures.sides[TEXTURE_WEST].ref,
			&g->textures.sides[TEXTURE_WEST].bpp, &g->textures.sides[TEXTURE_WEST].line_length, &g->textures.sides[TEXTURE_WEST].endian);
	if (!g->textures.sides[TEXTURE_WEST].addr)
		return (cub_errors_setter(g, "Failed to get data addr of west xpm."));


	int		i = -1;
	char	*path[6] = {"assets/hud/health_bar/0.xpm", "assets/hud/health_bar/1.xpm", "assets/hud/health_bar/2.xpm", "assets/hud/health_bar/3.xpm", "assets/hud/health_bar/4.xpm", "assets/hud/health_bar/5.xpm"};
	while (++i < 6)
	{
		g->textures.health_bar[i].ref = mlx_xpm_file_to_image(g->mlx, path[i], &it.i, &it.j);
		if (!g->textures.health_bar[i].ref)
			return (cub_errors_setter(g, "Failed to get data addr of health_bar xpm."));
		g->textures.health_bar[i].addr = mlx_get_data_addr(g->textures.health_bar[i].ref,
				&g->textures.health_bar[i].bpp, &g->textures.health_bar[i].line_length, &g->textures.health_bar[i].endian);
		if (!g->textures.health_bar[i].addr)
			return (cub_errors_setter(g, "Failed to get data addr of health_bar xpm."));
	}

	g->textures.wall_1.ref = mlx_xpm_file_to_image(g->mlx, "assets/textures/1.xpm", &it.i, &it.j);
	if (!g->textures.wall_1.ref)
		return (cub_errors_setter(g, "Failed to get data addr of wall_1 xpm."));
	g->textures.wall_1.addr = mlx_get_data_addr(g->textures.wall_1.ref,
			&g->textures.wall_1.bpp, &g->textures.wall_1.line_length, &g->textures.wall_1.endian);
	if (!g->textures.wall_1.addr)
		return (cub_errors_setter(g, "Failed to get data addr of wall_1 xpm."));
	g->textures.wall_2.ref = mlx_xpm_file_to_image(g->mlx, "assets/textures/2.xpm", &it.i, &it.j);
	if (!g->textures.wall_2.ref)
		return (cub_errors_setter(g, "Failed to get data addr of wall_2 xpm."));
	g->textures.wall_2.addr = mlx_get_data_addr(g->textures.wall_2.ref,
			&g->textures.wall_2.bpp, &g->textures.wall_2.line_length, &g->textures.wall_2.endian);
	if (!g->textures.wall_2.addr)
		return (cub_errors_setter(g, "Failed to get data addr of wall_2 xpm."));
	g->textures.wall_3.ref = mlx_xpm_file_to_image(g->mlx, "assets/textures/3.xpm", &it.i, &it.j);
	if (!g->textures.wall_3.ref)
		return (cub_errors_setter(g, "Failed to get data addr of wall_3 xpm."));
	g->textures.wall_3.addr = mlx_get_data_addr(g->textures.wall_3.ref,
			&g->textures.wall_3.bpp, &g->textures.wall_3.line_length, &g->textures.wall_3.endian);
	if (!g->textures.wall_3.addr)
		return (cub_errors_setter(g, "Failed to get data addr of wall_3 xpm."));
	g->textures.wall_4.ref = mlx_xpm_file_to_image(g->mlx, "assets/textures/4.xpm", &it.i, &it.j);
	if (!g->textures.wall_4.ref)
		return (cub_errors_setter(g, "Failed to get data addr of wall_4 xpm."));
	g->textures.wall_4.addr = mlx_get_data_addr(g->textures.wall_4.ref,
			&g->textures.wall_4.bpp, &g->textures.wall_3.line_length, &g->textures.wall_4.endian);
	if (!g->textures.wall_4.addr)
		return (cub_errors_setter(g, "Failed to get data addr of wall_4 xpm."));
	g->textures.wall_5.ref = mlx_xpm_file_to_image(g->mlx, "assets/textures/5.xpm", &it.i, &it.j);
	if (!g->textures.wall_5.ref)
		return (cub_errors_setter(g, "Failed to get data addr of wall_5 xpm."));
	g->textures.wall_5.addr = mlx_get_data_addr(g->textures.wall_5.ref,
			&g->textures.wall_5.bpp, &g->textures.wall_5.line_length, &g->textures.wall_5.endian);
	if (!g->textures.wall_5.addr)
		return (cub_errors_setter(g, "Failed to get data addr of wall_5 xpm."));
		
	g->textures.door.ref = mlx_xpm_file_to_image(g->mlx, "assets/textures/door.xpm", &it.i, &it.j);
	if (!g->textures.door.ref)
		return (cub_errors_setter(g, "Failed to get data addr of door xpm."));
	g->textures.door.addr = mlx_get_data_addr(g->textures.door.ref,
			&g->textures.door.bpp, &g->textures.door.line_length, &g->textures.door.endian);
	if (!g->textures.door.addr)
		return (cub_errors_setter(g, "Failed to get data addr of door xpm."));

	g->textures.ceil.ref = mlx_xpm_file_to_image(g->mlx, "assets/textures/1.xpm", &it.i, &it.j);
	if (!g->textures.ceil.ref)
		return (cub_errors_setter(g, "Failed to get data addr of ceil xpm."));
	g->textures.ceil.addr = mlx_get_data_addr(g->textures.ceil.ref,
			&g->textures.ceil.bpp, &g->textures.ceil.line_length, &g->textures.ceil.endian);
	if (!g->textures.ceil.addr)
		return (cub_errors_setter(g, "Failed to get data addr of ceil xpm."));

	g->textures.floor.ref = mlx_xpm_file_to_image(g->mlx, "assets/textures/3.xpm", &it.i, &it.j);
	if (!g->textures.floor.ref)
		return (cub_errors_setter(g, "Failed to get data addr of floor xpm."));
	g->textures.floor.addr = mlx_get_data_addr(g->textures.floor.ref,
			&g->textures.floor.bpp, &g->textures.floor.line_length, &g->textures.floor.endian);
	if (!g->textures.floor.addr)
		return (cub_errors_setter(g, "Failed to get data addr of floor xpm."));
	
	return (RETURN_SUCCESS);
}

int	cub_init_objects(t_game *g)
{
	t_iterators	it;

	g->textures.object_path[OBJECT_BARREL][0] = "assets/sprites/static/barrel.xpm";
	g->textures.object_n_of_frames[OBJECT_BARREL] = 1;
	g->textures.object_frame_rate[OBJECT_BARREL] = 0;
	g->textures.object_scale[OBJECT_BARREL] = 1;
	
	g->textures.object_path[OBJECT_PILLAR][0] = "assets/sprites/static/pillar.xpm";
	g->textures.object_n_of_frames[OBJECT_PILLAR] = 1;
	g->textures.object_frame_rate[OBJECT_PILLAR] = 0;
	g->textures.object_scale[OBJECT_PILLAR] = 1;

	g->textures.object_path[OBJECT_LAMP][0] = "assets/sprites/static/lamp.xpm";
	g->textures.object_n_of_frames[OBJECT_LAMP] = 1;
	g->textures.object_frame_rate[OBJECT_LAMP] = 0;
	g->textures.object_scale[OBJECT_LAMP] = 1;

	g->textures.object_path[OBJECT_GREEN_LIGHT][0] = "assets/sprites/animated/green_light/0.xpm";
	g->textures.object_path[OBJECT_GREEN_LIGHT][1] = "assets/sprites/animated/green_light/1.xpm";
	g->textures.object_path[OBJECT_GREEN_LIGHT][2] = "assets/sprites/animated/green_light/2.xpm";
	g->textures.object_path[OBJECT_GREEN_LIGHT][3] = "assets/sprites/animated/green_light/3.xpm";
	g->textures.object_n_of_frames[OBJECT_GREEN_LIGHT] = 4;
	g->textures.object_frame_rate[OBJECT_GREEN_LIGHT] = 200;
	g->textures.object_scale[OBJECT_GREEN_LIGHT] = 1;

	g->textures.object_path[OBJECT_MEDKIT][0] = "assets/sprites/medkit.xpm";
	g->textures.object_n_of_frames[OBJECT_MEDKIT] = 1;
	g->textures.object_frame_rate[OBJECT_MEDKIT] = 0;
	g->textures.object_scale[OBJECT_MEDKIT] = 1;

	it.i = -1;
	while (++it.i < N_OF_OBJECTS)
	{
		it.j = -1;
		while (++it.j < g->textures.object_n_of_frames[it.i])
		{
			g->textures.object_image[it.i][it.j].ref = mlx_xpm_file_to_image(g->mlx,
				g->textures.object_path[it.i][it.j],
				&g->textures.object_dimension[it.i].j,
				&g->textures.object_dimension[it.i].i);
			if (!g->textures.object_image[it.i][it.j].ref)
				return (cub_errors_setter(g, "Failed to get data addr of object xpm."));
			g->textures.object_image[it.i][it.j].addr = mlx_get_data_addr(g->textures.object_image[it.i][it.j].ref,
					&g->textures.object_image[it.i][it.j].bpp, &g->textures.object_image[it.i][it.j].line_length,
					&g->textures.object_image[it.i][it.j].endian);
			if (!g->textures.object_image[it.i][it.j].addr)
				return (cub_errors_setter(g, "Failed to get data addr of object xpm."));
		}
	}
	return (RETURN_SUCCESS);
}

int	cub_init(t_game *g)
{
	int	x, y;

	mlx_mouse_get_pos(g->win.ref, &x, &y);
	g->player.health = 50;
	g->mouse.x = x;
	g->player.shooting = false;
	g->display_map = false;
	g->buffer = (float *) malloc(sizeof(float) * NUM_RAYS);
	if (!g->buffer)
		return (cub_errors_setter(g, ERR_MALLOC));
	g->allocated.buffer = true;
	if (cub_init_textures(g))
		return (RETURN_FAILURE);
	if (cub_init_sprites(g))
		return (RETURN_FAILURE);
	return (RETURN_SUCCESS);
}