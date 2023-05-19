/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 01:55:23 by absalhi           #+#    #+#             */
/*   Updated: 2023/05/19 08:21:23 by absalhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define HEALTHBAR_FRAMES 6
#define DIGITS_FRAMES 10

static void	assign_healthbar_paths(char *path[HEALTHBAR_FRAMES])
{
	path[0] = HEALTHBAR_0;
	path[1] = HEALTHBAR_1;
	path[2] = HEALTHBAR_2;
	path[3] = HEALTHBAR_3;
	path[4] = HEALTHBAR_4;
	path[5] = HEALTHBAR_5;
}

int	init_healthbar(t_game *g)
{
	int			i;
	char		*path[HEALTHBAR_FRAMES];
	t_iterators	it;

	assign_healthbar_paths(path);
	i = -1;
	while (++i < HEALTHBAR_FRAMES)
	{
		g->textures.health_bar[i].ref
			= mlx_xpm_file_to_image(g->mlx, path[i], &it.i, &it.j);
		if (!g->textures.health_bar[i].ref)
			return (errors_setter(g, FAIL_HEALTHBAR_LOAD));
		g->textures.health_bar[i].addr
			= mlx_get_data_addr(g->textures.health_bar[i].ref,
				&g->textures.health_bar[i].bpp,
				&g->textures.health_bar[i].line_length,
				&g->textures.health_bar[i].endian);
		if (!g->textures.health_bar[i].addr)
			return (errors_setter(g, FAIL_HEALTHBAR_DATA));
	}
	return (RETURN_SUCCESS);
}

static void	assign_digits_paths(char *path[DIGITS_FRAMES])
{
	path[0] = DIGITS_0;
	path[1] = DIGITS_1;
	path[2] = DIGITS_2;
	path[3] = DIGITS_3;
	path[4] = DIGITS_4;
	path[5] = DIGITS_5;
	path[6] = DIGITS_6;
	path[7] = DIGITS_7;
	path[8] = DIGITS_8;
	path[9] = DIGITS_9;
}

int	init_digits(t_game *g)
{
	int			i;
	char		*path[DIGITS_FRAMES];
	t_iterators	it;

	i = -1;
	assign_digits_paths(path);
	while (++i < DIGITS_FRAMES)
	{
		g->textures.digits[i].ref
			= mlx_xpm_file_to_image(g->mlx, path[i], &it.i, &it.j);
		if (!g->textures.digits[i].ref)
			return (errors_setter(g, FAIL_DIGITS_LOAD));
		g->textures.digits[i].addr
			= mlx_get_data_addr(g->textures.digits[i].ref,
				&g->textures.digits[i].bpp,
				&g->textures.digits[i].line_length,
				&g->textures.digits[i].endian);
		if (!g->textures.digits[i].addr)
			return (errors_setter(g, FAIL_DIGITS_DATA));
	}
	return (RETURN_SUCCESS);
}
