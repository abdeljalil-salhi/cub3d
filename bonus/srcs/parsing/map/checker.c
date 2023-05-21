/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 17:19:06 by absalhi           #+#    #+#             */
/*   Updated: 2023/05/21 05:51:46 by absalhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	is_invalid_border(int c)
{
	if (c == 0 || c == PLAYER)
		return (true);
	return (false);
}

static int	check_map_components(t_game *g, int i, int j)
{
	if (j + 1 < g->map.width && g->map.arr[i][j] == -1
		&& is_invalid_border(g->map.arr[i][j + 1]))
		return (errors_setter(g, MAP_INVALID_BORDER));
	if (i + 1 < g->map.height && g->map.arr[i][j] == -1
		&& is_invalid_border(g->map.arr[i + 1][j]))
		return (errors_setter(g, MAP_INVALID_BORDER));
	if (j + 1 < g->map.width && is_invalid_border(g->map.arr[i][j])
		&& g->map.arr[i][j + 1] == -1)
		return (errors_setter(g, MAP_INVALID_BORDER));
	if (i + 1 < g->map.height && is_invalid_border(g->map.arr[i][j])
		&& g->map.arr[i + 1][j] == -1)
		return (errors_setter(g, MAP_INVALID_BORDER));
	return (RETURN_SUCCESS);
}

int	check_map_borders_and_components(t_game *g)
{
	t_iterators	it;

	it.i = -1;
	while (++it.i < g->map.width)
		if (g->map.arr[0][it.i] == 0
			|| g->map.arr[g->map.height - 1][it.i] == 0)
			return (errors_setter(g, MAP_INVALID_BORDER));
	it.i = -1;
	while (++it.i < g->map.height)
		if (g->map.arr[it.i][0] == 0
			|| g->map.arr[it.i][g->map.width - 1] == 0)
			return (errors_setter(g, MAP_INVALID_BORDER));
	it.i = -1;
	while (++it.i < g->map.height)
	{
		it.j = -1;
		while (++it.j < g->map.width)
			if (check_map_components(g, it.i, it.j))
				return (RETURN_FAILURE);
	}
	return (RETURN_SUCCESS);
}

int	check_player_occurences(t_game *g)
{
	int	i;
	int	occur;

	occur = 0;
	i = -1;
	while (++i < g->map.height)
		occur += count_int_occurences(g->map.arr[i], g->map.width, PLAYER);
	if (!occur)
		return (errors_setter(g, MAP_NO_PLAYERS));
	else if (occur > 1)
		return (errors_setter(g, MAP_MULTIPLE_PLAYERS));
	return (RETURN_SUCCESS);
}

int	map_check(t_game *g, char *line)
{
	static unsigned int	lines_before_map = 0;

	if (!line_empty(line) && !g->parsing.is_map)
	{
		g->parsing.is_map = true;
		g->parsing.lines_before_map = lines_before_map;
	}
	if (!g->parsing.is_map)
		lines_before_map++;
	return (RETURN_SUCCESS);
}
