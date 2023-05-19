/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 00:20:08 by absalhi           #+#    #+#             */
/*   Updated: 2023/05/19 02:39:04 by absalhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	init_textures(t_game *g)
{
	if (init_healthbar(g))
		return (RETURN_FAILURE);
	if (init_walls(g))
		return (RETURN_FAILURE);
	if (init_digits(g))
		return (RETURN_FAILURE);
	if (init_ceil(g))
		return (RETURN_FAILURE);
	if (init_floor(g))
		return (RETURN_FAILURE);
	if (init_red_splash(g))
		return (RETURN_FAILURE);
	if (init_green_splash(g))
		return (RETURN_FAILURE);
	if (init_game_over(g))
		return (RETURN_FAILURE);
	return (RETURN_SUCCESS);
}

int	init_sprites(t_game *g)
{
	if (init_weapon(g))
		return (RETURN_FAILURE);
	if (init_objects(g))
		return (RETURN_FAILURE);
	return (RETURN_SUCCESS);
}

int	init_game(t_game *g)
{
	t_iterators	it;

	mlx_mouse_get_pos(g->win.ref, &it.i, &it.j);
	g->player.health = 100;
	g->mouse.x = it.i;
	g->player.shooting = false;
	g->display_map = false;
	g->buffer = (float *) malloc(sizeof(float) * NUM_RAYS);
	if (!g->buffer)
		return (errors_setter(g, ERR_MALLOC));
	g->allocated.buffer = true;
	if (init_textures(g))
		return (RETURN_FAILURE);
	if (init_sprites(g))
		return (RETURN_FAILURE);
	if (init_sounds(g))
		return (RETURN_FAILURE);
	return (RETURN_SUCCESS);
}
