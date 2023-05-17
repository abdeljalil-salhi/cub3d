/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 00:20:08 by absalhi           #+#    #+#             */
/*   Updated: 2023/05/17 08:11:25 by absalhi          ###   ########.fr       */
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

	i = -1;
	char *path_walls[5] = {"assets/textures/1.xpm", "assets/textures/2.xpm", "assets/textures/3.xpm", "assets/textures/4.xpm", "assets/textures/5.xpm"};
	while (++i < 5)
	{
		g->textures.walls[i].ref = mlx_xpm_file_to_image(g->mlx, path_walls[i], &it.i, &it.j);
		if (!g->textures.walls[i].ref)
			return (cub_errors_setter(g, "Failed to get data addr of walls xpm."));
		g->textures.walls[i].addr = mlx_get_data_addr(g->textures.walls[i].ref,
				&g->textures.walls[i].bpp, &g->textures.walls[i].line_length, &g->textures.walls[i].endian);
		if (!g->textures.walls[i].addr)
			return (cub_errors_setter(g, "Failed to get data addr of walls xpm."));
	}

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

	g->textures.splash[RED_SPLASH].ref = mlx_xpm_file_to_image(g->mlx, "assets/hud/splash/red.xpm", &it.i, &it.j);
	if (!g->textures.splash[RED_SPLASH].ref)
		return (cub_errors_setter(g, "Failed to get data addr of red splash xpm."));
	g->textures.splash[RED_SPLASH].addr = mlx_get_data_addr(g->textures.splash[RED_SPLASH].ref,
			&g->textures.splash[RED_SPLASH].bpp, &g->textures.splash[RED_SPLASH].line_length, &g->textures.splash[RED_SPLASH].endian);
	if (!g->textures.splash[RED_SPLASH].addr)
		return (cub_errors_setter(g, "Failed to get data addr of red splash xpm."));

	g->textures.splash[GREEN_SPLASH].ref = mlx_xpm_file_to_image(g->mlx, "assets/hud/splash/green.xpm", &it.i, &it.j);
	if (!g->textures.splash[GREEN_SPLASH].ref)
		return (cub_errors_setter(g, "Failed to get data addr of green splash xpm."));
	g->textures.splash[GREEN_SPLASH].addr = mlx_get_data_addr(g->textures.splash[GREEN_SPLASH].ref,
			&g->textures.splash[GREEN_SPLASH].bpp, &g->textures.splash[GREEN_SPLASH].line_length, &g->textures.splash[GREEN_SPLASH].endian);
	if (!g->textures.splash[GREEN_SPLASH].addr)
		return (cub_errors_setter(g, "Failed to get data addr of green splash xpm."));

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

	g->textures.object_path[OBJECT_DOOR][0] = "assets/door/0.xpm";
	g->textures.object_path[OBJECT_DOOR][1] = "assets/door/1.xpm";
	g->textures.object_path[OBJECT_DOOR][2] = "assets/door/2.xpm";
	g->textures.object_path[OBJECT_DOOR][3] = "assets/door/3.xpm";
	g->textures.object_n_of_frames[OBJECT_DOOR] = 4;
	g->textures.object_frame_rate[OBJECT_DOOR] = 200;
	g->textures.object_scale[OBJECT_DOOR] = 1;

	g->textures.object_path[OBJECT_MEDKIT][0] = "assets/sprites/medkit.xpm";
	g->textures.object_n_of_frames[OBJECT_MEDKIT] = 1;
	g->textures.object_frame_rate[OBJECT_MEDKIT] = 0;
	g->textures.object_scale[OBJECT_MEDKIT] = 1;

	g->textures.object_path[OBJECT_SOLDIER_WALK][0] = "assets/sprites/enemy/soldier/walk/0.xpm";
	g->textures.object_path[OBJECT_SOLDIER_WALK][1] = "assets/sprites/enemy/soldier/walk/1.xpm";
	g->textures.object_path[OBJECT_SOLDIER_WALK][2] = "assets/sprites/enemy/soldier/walk/2.xpm";
	g->textures.object_path[OBJECT_SOLDIER_WALK][3] = "assets/sprites/enemy/soldier/walk/3.xpm";
	g->textures.object_n_of_frames[OBJECT_SOLDIER_WALK] = 4;
	g->textures.object_frame_rate[OBJECT_SOLDIER_WALK] = 200;
	g->textures.object_scale[OBJECT_SOLDIER_WALK] = 0.8;

	g->textures.object_path[OBJECT_SOLDIER_DAMAGED][0] = "assets/sprites/enemy/soldier/damaged/0.xpm";
	g->textures.object_n_of_frames[OBJECT_SOLDIER_DAMAGED] = 1;
	g->textures.object_frame_rate[OBJECT_SOLDIER_DAMAGED] = 0;
	g->textures.object_scale[OBJECT_SOLDIER_DAMAGED] = 0.8;

	g->textures.object_path[OBJECT_SOLDIER_ATTACK][0] = "assets/sprites/enemy/soldier/attack/0.xpm";
	g->textures.object_path[OBJECT_SOLDIER_ATTACK][1] = "assets/sprites/enemy/soldier/attack/1.xpm";
	g->textures.object_n_of_frames[OBJECT_SOLDIER_ATTACK] = 2;
	g->textures.object_frame_rate[OBJECT_SOLDIER_ATTACK] = 200;
	g->textures.object_scale[OBJECT_SOLDIER_ATTACK] = 0.8;

	g->textures.object_path[OBJECT_SOLDIER_DEATH][0] = "assets/sprites/enemy/soldier/death/0.xpm";
	g->textures.object_path[OBJECT_SOLDIER_DEATH][1] = "assets/sprites/enemy/soldier/death/1.xpm";
	g->textures.object_path[OBJECT_SOLDIER_DEATH][2] = "assets/sprites/enemy/soldier/death/2.xpm";
	g->textures.object_path[OBJECT_SOLDIER_DEATH][3] = "assets/sprites/enemy/soldier/death/3.xpm";
	g->textures.object_path[OBJECT_SOLDIER_DEATH][4] = "assets/sprites/enemy/soldier/death/4.xpm";
	g->textures.object_path[OBJECT_SOLDIER_DEATH][5] = "assets/sprites/enemy/soldier/death/5.xpm";
	g->textures.object_path[OBJECT_SOLDIER_DEATH][6] = "assets/sprites/enemy/soldier/death/6.xpm";
	g->textures.object_path[OBJECT_SOLDIER_DEATH][7] = "assets/sprites/enemy/soldier/death/7.xpm";
	g->textures.object_path[OBJECT_SOLDIER_DEATH][8] = "assets/sprites/enemy/soldier/death/8.xpm";
	g->textures.object_n_of_frames[OBJECT_SOLDIER_DEATH] = 9;
	g->textures.object_frame_rate[OBJECT_SOLDIER_DEATH] = 50;
	g->textures.object_scale[OBJECT_SOLDIER_DEATH] = 0.8;

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

int	init_sounds(t_game *g);
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
	if (init_sounds(g))
		return (RETURN_FAILURE);
	return (RETURN_SUCCESS);
}