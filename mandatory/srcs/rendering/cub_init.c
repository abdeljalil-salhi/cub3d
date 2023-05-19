/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isalhi <isalhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 00:20:08 by absalhi           #+#    #+#             */
/*   Updated: 2023/05/18 18:11:18 by isalhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	cub_load_textures(t_game *g)
{
	g->textures[TEXT_N].addr = mlx_get_data_addr(g->textures[TEXT_N].ref,
			&g->textures[TEXT_N].bpp, &g->textures[TEXT_N].line_length,
			&g->textures[TEXT_N].endian);
	if (!g->textures[TEXT_N].addr)
		return (cub_errors_setter(g, "Failed to get data addr of north xpm."));
	g->textures[TEXT_S].addr = mlx_get_data_addr(g->textures[TEXT_S].ref,
			&g->textures[TEXT_S].bpp, &g->textures[TEXT_S].line_length,
			&g->textures[TEXT_S].endian);
	if (!g->textures[TEXT_S].addr)
		return (cub_errors_setter(g, "Failed to get data addr of south xpm."));
	g->textures[TEXT_E].addr = mlx_get_data_addr(g->textures[TEXT_E].ref,
			&g->textures[TEXT_E].bpp, &g->textures[TEXT_E].line_length,
			&g->textures[TEXT_E].endian);
	if (!g->textures[TEXT_E].addr)
		return (cub_errors_setter(g, "Failed to get data addr of east xpm."));
	g->textures[TEXT_W].addr = mlx_get_data_addr(g->textures[TEXT_W].ref,
			&g->textures[TEXT_W].bpp, &g->textures[TEXT_W].line_length,
			&g->textures[TEXT_W].endian);
	if (!g->textures[TEXT_W].addr)
		return (cub_errors_setter(g, "Failed to get data addr of west xpm."));
	return (RETURN_SUCCESS);
}

int	cub_init_textures(t_game *g)
{
	t_iterators	it;

	g->textures[TEXT_N].ref = mlx_xpm_file_to_image(g->mlx, g->assets.north,
			&it.i, &it.j);
	if (!g->textures[TEXT_N].ref)
		return (cub_errors_setter(g, "Failed to get data addr of north xpm."));
	g->textures[TEXT_S].ref = mlx_xpm_file_to_image(g->mlx, g->assets.south,
			&it.i, &it.j);
	if (!g->textures[TEXT_S].ref)
		return (cub_errors_setter(g, "Failed to get data addr of south xpm."));
	g->textures[TEXT_E].ref = mlx_xpm_file_to_image(g->mlx, g->assets.east,
			&it.i, &it.j);
	if (!g->textures[TEXT_E].ref)
		return (cub_errors_setter(g, "Failed to get data addr of east xpm."));
	g->textures[TEXT_W].ref = mlx_xpm_file_to_image(g->mlx, g->assets.west,
			&it.i, &it.j);
	if (!g->textures[TEXT_W].ref)
		return (cub_errors_setter(g, "Failed to get data addr of west xpm."));
	cub_load_textures(g);
	return (RETURN_SUCCESS);
}

int	cub_init(t_game *g)
{
	if (cub_init_textures(g))
		return (RETURN_FAILURE);
	return (RETURN_SUCCESS);
}
