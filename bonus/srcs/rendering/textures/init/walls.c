/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 02:01:36 by absalhi           #+#    #+#             */
/*   Updated: 2023/05/19 08:22:04 by absalhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define WALLS_FRAMES 5

static void	assign_walls_paths(char *path[WALLS_FRAMES])
{
	path[0] = WALL_0;
	path[1] = WALL_1;
	path[2] = WALL_2;
	path[3] = WALL_3;
	path[4] = WALL_4;
}

int	init_walls(t_game *g)
{
	int			i;
	char		*path[WALLS_FRAMES];
	t_iterators	it;

	assign_walls_paths(path);
	i = -1;
	while (++i < WALLS_FRAMES)
	{
		g->textures.walls[i].ref
			= mlx_xpm_file_to_image(g->mlx, path[i], &it.i, &it.j);
		if (!g->textures.walls[i].ref)
			return (errors_setter(g, FAIL_WALL_LOAD));
		g->textures.walls[i].addr
			= mlx_get_data_addr(g->textures.walls[i].ref,
				&g->textures.walls[i].bpp,
				&g->textures.walls[i].line_length,
				&g->textures.walls[i].endian);
		if (!g->textures.walls[i].addr)
			return (errors_setter(g, FAIL_WALL_DATA));
	}
	return (RETURN_SUCCESS);
}
