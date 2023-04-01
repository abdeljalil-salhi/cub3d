/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_green_light.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 00:21:38 by absalhi           #+#    #+#             */
/*   Updated: 2023/04/01 00:49:31 by absalhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	cub_init_green_light(t_game *g)
{
	t_iterators	it;
	int			frame;

	g->textures.green_light.path = (char **) malloc(sizeof(char *) * 4);
	if (!g->textures.green_light.path)
		return (cub_errors_setter(g, ERR_MALLOC));
	g->allocated.green_light = true;
	g->textures.green_light.path[0] = "assets/sprites/green_light/0.xpm";
	g->textures.green_light.path[1] = "assets/sprites/green_light/1.xpm";
	g->textures.green_light.path[2] = "assets/sprites/green_light/2.xpm";
	g->textures.green_light.path[3] = "assets/sprites/green_light/3.xpm";
	frame = g->textures.green_light.frame;
	g->textures.green_light.image.ref = mlx_xpm_file_to_image(g->mlx,
			g->textures.green_light.path[frame], &it.i, &it.j);
	if (!g->textures.green_light.image.ref)
		return (cub_errors_setter(g, "Failed to load green light xpm."));
	g->textures.green_light.image.addr = mlx_get_data_addr(g->textures.green_light.image.ref,
			&g->textures.green_light.image.bpp, &g->textures.green_light.image.line_length,
			&g->textures.green_light.image.endian);
	if (!g->textures.green_light.image.addr)
		return (cub_errors_setter(g, "Failed to get data addr of green light xpm."));
	return (RETURN_SUCCESS);
}
