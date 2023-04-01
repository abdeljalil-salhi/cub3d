/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 00:20:08 by absalhi           #+#    #+#             */
/*   Updated: 2023/04/01 00:56:41 by absalhi          ###   ########.fr       */
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

	g->textures.redbrick.ref = mlx_xpm_file_to_image(g->mlx, "assets/textures/redbrick.xpm", &it.i, &it.j);
	g->textures.redbrick.addr = mlx_get_data_addr(g->textures.redbrick.ref,
			&g->textures.redbrick.bpp, &g->textures.redbrick.line_length, &g->textures.redbrick.endian);
	if (!g->textures.redbrick.addr)
		return (cub_errors_setter(g, "Failed to get data addr of redbrick xpm."));
	g->textures.bluestone.ref = mlx_xpm_file_to_image(g->mlx, "assets/textures/bluestone.xpm", &it.i, &it.j);
	g->textures.bluestone.addr = mlx_get_data_addr(g->textures.bluestone.ref,
			&g->textures.bluestone.bpp, &g->textures.bluestone.line_length, &g->textures.bluestone.endian);
	if (!g->textures.bluestone.addr)
		return (cub_errors_setter(g, "Failed to get data addr of bluestone xpm."));
	g->textures.eagle.ref = mlx_xpm_file_to_image(g->mlx, "assets/textures/eagle.xpm", &it.i, &it.j);
	g->textures.eagle.addr = mlx_get_data_addr(g->textures.eagle.ref,
			&g->textures.eagle.bpp, &g->textures.eagle.line_length, &g->textures.eagle.endian);
	if (!g->textures.eagle.addr)
		return (cub_errors_setter(g, "Failed to get data addr of eagle xpm."));
	// g->textures.pillar.ref = mlx_xpm_file_to_image(g->mlx, "assets/textures/pillar.xpm", &it.i, &it.j);
	// g->textures.pillar.addr = mlx_get_data_addr(g->textures.pillar.ref,
	// 		&g->textures.pillar.bpp, &g->textures.eagle.line_length, &g->textures.pillar.endian);
	// g->textures.wood.ref = mlx_xpm_file_to_image(g->mlx, "assets/textures/wood.xpm", &it.i, &it.j);
	// g->textures.wood.addr = mlx_get_data_addr(g->textures.wood.ref,
	// 		&g->textures.wood.bpp, &g->textures.wood.line_length, &g->textures.wood.endian);
	// g->textures.barrel.ref = mlx_xpm_file_to_image(g->mlx, "assets/textures/barrel.xpm", &it.i, &it.j);
	// g->textures.barrel.addr = mlx_get_data_addr(g->textures.barrel.ref,
	// 		&g->textures.barrel.bpp, &g->textures.barrel.line_length, &g->textures.barrel.endian);
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
