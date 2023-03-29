/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 21:28:45 by absalhi           #+#    #+#             */
/*   Updated: 2023/03/29 03:32:40 by absalhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	cub_map_init_helper(t_game *g, t_cub_map_init *s)
{
	g->parsing.lowest_indent = s->lowest_indent;
	g->map.width = s->width;
	g->map.height = s->height;
	close(g->map.file.fd);
	if (cub_file_open(g, &g->map.file.fd, g->map.file.path))
		return (RETURN_FAILURE);
	s->it.i = -1;
	while (++s->it.i < g->parsing.lines_before_map + 1)
		free(get_next_line(g->map.file.fd));
	if (DEBUG)
		printf("lowest_indent: %d width: %d height: %d lines_before_map: %d\n",
			s->lowest_indent, s->width, s->height, g->parsing.lines_before_map);
	g->map.arr = (int **) malloc(sizeof(int *) * g->map.height);
	if (!g->map.arr)
		return (cub_errors_setter(g, ERR_MALLOC));
	g->parsing.map_initialized = true;
	return (RETURN_SUCCESS);
}

int	cub_map_init(t_game *g)
{
	t_cub_map_init	s;

	ft_bzero(&s, sizeof(t_cub_map_init));
	s.lowest_indent = -1;
	while (true)
	{
		s.quick_line = get_next_line(g->map.file.fd);
		s.height++;
		if (!s.quick_line)
			break ;
		if (cub_line_empty(s.quick_line))
		{
			free(s.quick_line);
			continue ;
		}
		cub_map_init_norm(&s);
		free(s.quick_line);
	}
	return (cub_map_init_helper(g, &s));
}

typedef struct s_cub_map_parse
{
	int	j;
	int	k;
}	t_cub_map_parse;

static void	cub_map_parse_helper_setter(t_game *g,
		int i, int j, double degree)
{
	g->map.arr[i][j] = 2;
	g->player.pos.x = TILE_SIZE * j + TILE_SIZE / 2;
	g->player.pos.y = TILE_SIZE * i + TILE_SIZE / 2;
	g->player.width = PLAYER_WIDTH;
	g->player.height = PLAYER_HEIGHT;
	g->player.angle = degree;
	g->player.speed = PLAYER_SPEED;
	g->player.rot_speed = PLAYER_ROTATION_SPEED;
}

static int	cub_map_parse_helper(char *line, t_game *g,
		int i, t_cub_map_parse *s)
{
	if (line[s->k] == ' ')
		g->map.arr[i][s->j] = -1;
	else if (line[s->k] == '0')
		g->map.arr[i][s->j] = 0;
	else if (line[s->k] == '1')
		g->map.arr[i][s->j] = 1;
	else if (line[s->k] == 'N')
		cub_map_parse_helper_setter(g, i, s->j, 3 * M_PI / 2);
	else if (line[s->k] == 'S')
		cub_map_parse_helper_setter(g, i, s->j, M_PI / 2);
	else if (line[s->k] == 'E')
		cub_map_parse_helper_setter(g, i, s->j, 2 * M_PI);
	else if (line[s->k] == 'W')
		cub_map_parse_helper_setter(g, i, s->j, M_PI);
	else
		return (cub_errors_setter(g, MAP_INVALID_CHAR));
	s->k++;
	return (RETURN_SUCCESS);
}

int	cub_map_parse(t_game *g, char *line)
{
	static int		i = 0;
	t_cub_map_parse	s;

	if (!g->parsing.map_initialized)
		if (cub_map_init(g))
			return (RETURN_FAILURE);
	if (i >= g->map.height + 1)
		return (cub_errors_setter(g, MAP_INDEX_OUT_OF_RANGE));
	g->map.arr[i] = (int *) malloc(sizeof(int) * g->map.width);
	if (!g->map.arr[i])
		return (cub_errors_setter(g, ERR_MALLOC));
	s.j = -1;
	s.k = g->parsing.lowest_indent;
	while (++s.j < g->map.width)
	{
		if (line[s.k] && line[s.k] != '\n')
		{
			if (cub_map_parse_helper(line, g, i, &s))
				return (RETURN_FAILURE);
		}
		else
			g->map.arr[i][s.j] = -1;
	}
	i++;
	return (RETURN_SUCCESS);
}
