/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 02:11:04 by absalhi           #+#    #+#             */
/*   Updated: 2023/05/19 06:19:48 by absalhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	init_ceil(t_game *g)
{
	t_iterators	it;

	g->textures.ceil.ref
		= mlx_xpm_file_to_image(g->mlx, CEIL_0, &it.i, &it.j);
	if (!g->textures.ceil.ref)
		return (errors_setter(g, FAIL_CEIL_LOAD));
	g->textures.ceil.addr
		= mlx_get_data_addr(g->textures.ceil.ref,
			&g->textures.ceil.bpp,
			&g->textures.ceil.line_length,
			&g->textures.ceil.endian);
	if (!g->textures.ceil.addr)
		return (errors_setter(g, FAIL_CEIL_DATA));
	return (RETURN_SUCCESS);
}

int	init_floor(t_game *g)
{
	t_iterators	it;

	g->textures.floor.ref
		= mlx_xpm_file_to_image(g->mlx, FLOOR_0, &it.i, &it.j);
	if (!g->textures.floor.ref)
		return (errors_setter(g, FAIL_FLOOR_LOAD));
	g->textures.floor.addr
		= mlx_get_data_addr(g->textures.floor.ref,
			&g->textures.floor.bpp,
			&g->textures.floor.line_length,
			&g->textures.floor.endian);
	if (!g->textures.floor.addr)
		return (errors_setter(g, FAIL_FLOOR_DATA));
	return (RETURN_SUCCESS);
}

int	init_red_splash(t_game *g)
{
	t_iterators	it;

	g->textures.splash[RED_SPLASH].ref
		= mlx_xpm_file_to_image(g->mlx, RED_SPLASH_0, &it.i, &it.j);
	if (!g->textures.splash[RED_SPLASH].ref)
		return (errors_setter(g, FAIL_RED_SPLASH_LOAD));
	g->textures.splash[RED_SPLASH].addr
		= mlx_get_data_addr(g->textures.splash[RED_SPLASH].ref,
			&g->textures.splash[RED_SPLASH].bpp,
			&g->textures.splash[RED_SPLASH].line_length,
			&g->textures.splash[RED_SPLASH].endian);
	if (!g->textures.splash[RED_SPLASH].addr)
		return (errors_setter(g, FAIL_RED_SPLASH_DATA));
	return (RETURN_SUCCESS);
}

int	init_green_splash(t_game *g)
{
	t_iterators	it;

	g->textures.splash[GREEN_SPLASH].ref
		= mlx_xpm_file_to_image(g->mlx, GREEN_SPLASH_0, &it.i, &it.j);
	if (!g->textures.splash[GREEN_SPLASH].ref)
		return (errors_setter(g, FAIL_GREEN_SPLASH_LOAD));
	g->textures.splash[GREEN_SPLASH].addr
		= mlx_get_data_addr(g->textures.splash[GREEN_SPLASH].ref,
			&g->textures.splash[GREEN_SPLASH].bpp,
			&g->textures.splash[GREEN_SPLASH].line_length,
			&g->textures.splash[GREEN_SPLASH].endian);
	if (!g->textures.splash[GREEN_SPLASH].addr)
		return (errors_setter(g, FAIL_GREEN_SPLASH_DATA));
	return (RETURN_SUCCESS);
}

int	init_game_over(t_game *g)
{
	t_iterators	it;

	g->textures.game_over.ref
		= mlx_xpm_file_to_image(g->mlx, GAME_OVER_0, &it.i, &it.j);
	if (!g->textures.game_over.ref)
		return (errors_setter(g, FAIL_GAME_OVER_LOAD));
	g->textures.game_over.addr
		= mlx_get_data_addr(g->textures.game_over.ref,
			&g->textures.game_over.bpp,
			&g->textures.game_over.line_length,
			&g->textures.game_over.endian);
	if (!g->textures.game_over.addr)
		return (errors_setter(g, FAIL_GAME_OVER_DATA));
	return (RETURN_SUCCESS);
}
