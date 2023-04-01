/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 00:20:08 by absalhi           #+#    #+#             */
/*   Updated: 2023/04/01 05:17:36 by absalhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	cub_init_sprites(t_game *g)
{
	(void) g;
	// if (cub_init_green_light(g))
	// 	return (RETURN_FAILURE);
	return (RETURN_SUCCESS);
}

int	cub_init_textures(t_game *g)
{
	t_iterators	it;

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
	g->textures.sky.ref = mlx_xpm_file_to_image(g->mlx, "assets/sky.xpm", &it.i, &it.j);
	if (!g->textures.sky.ref)
		return (cub_errors_setter(g, "Failed to get data addr of sky xpm."));
	return (RETURN_SUCCESS);
}

int	cub_init(t_game *g)
{
	if (cub_init_textures(g))
		return (RETURN_FAILURE);
	if (cub_init_sprites(g))
		return (RETURN_FAILURE);
	return (RETURN_SUCCESS);
}

void	cub_free_textures(t_game *g)
{
	if (g->allocated.green_light)
		cub_free(g->textures.green_light.path);
}
