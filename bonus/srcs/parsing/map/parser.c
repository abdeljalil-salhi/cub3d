/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 21:28:45 by absalhi           #+#    #+#             */
/*   Updated: 2023/05/19 10:46:16 by absalhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

typedef struct s_parsing_iterators
{
	int	j;
	int	k;
}	t_parsing_iterators;

static int	map_struct_filler(t_game *g, t_parsing_analyzer *s)
{
	g->parsing.lowest_indent = s->lowest_indent;
	g->map.width = s->width;
	g->map.height = s->height;
	close(g->map.file.fd);
	if (file_open(g, &g->map.file.fd, g->map.file.path))
		return (RETURN_FAILURE);
	s->it.i = -1;
	while (++s->it.i < g->parsing.lines_before_map + 1)
		free_ptr(get_next_line(g->map.file.fd));
	g->objects = (t_object *) malloc(sizeof(t_object) * g->objects_count);
	if (!g->objects)
		return (errors_setter(g, ERR_MALLOC));
	g->map.arr = (int **) malloc(sizeof(int *) * g->map.height);
	if (!g->map.arr)
		return (errors_setter(g, ERR_MALLOC));
	g->parsing.map_initialized = true;
	return (RETURN_SUCCESS);
}

static void	player_setter(t_game *g, int i, int j, float degree)
{
	g->map.arr[i][j] = PLAYER;
	g->player.pos.x = TILE_SIZE * j + TILE_SIZE / 2;
	g->player.pos.y = TILE_SIZE * i + TILE_SIZE / 2;
	g->player.width = PLAYER_WIDTH;
	g->player.height = PLAYER_HEIGHT;
	g->player.angle = degree;
	g->player.speed = PLAYER_SPEED;
}

static int	map_parse_helper(char *line,
	t_game *g, int i, t_parsing_iterators *s)
{
	if (line[s->k] == ' ')
		g->map.arr[i][s->j] = -1;
	else if (line[s->k] >= '0' && line[s->k] <= '5')
		g->map.arr[i][s->j] = line[s->k] - 48;
	else if (line[s->k] == 'N')
		player_setter(g, i, s->j, 3 * M_PI / 2);
	else if (line[s->k] == 'S')
		player_setter(g, i, s->j, M_PI / 2);
	else if (line[s->k] == 'E')
		player_setter(g, i, s->j, 2 * M_PI);
	else if (line[s->k] == 'W')
		player_setter(g, i, s->j, M_PI);
	else if (is_object(line[s->k]))
		object_setter(g, line[s->k], i, s->j);
	else
		return (errors_setter(g, MAP_INVALID_CHAR));
	s->k++;
	return (RETURN_SUCCESS);
}

int	map_init(t_game *g)
{
	t_parsing_analyzer	s;

	ft_bzero(&s, sizeof(t_parsing_analyzer));
	s.lowest_indent = -1;
	while (true)
	{
		s.quick_line = get_next_line(g->map.file.fd);
		s.height++;
		if (!s.quick_line)
			break ;
		if (line_empty(s.quick_line))
		{
			free_ptr(s.quick_line);
			continue ;
		}
		map_analyzer(g, &s);
		free_ptr(s.quick_line);
	}
	return (map_struct_filler(g, &s));
}

int	map_parse(t_game *g, char *line)
{
	static int			i = 0;
	t_parsing_iterators	s;

	if (!g->parsing.map_initialized)
		if (map_init(g))
			return (RETURN_FAILURE);
	if (i >= g->map.height + 1)
		return (errors_setter(g, MAP_INDEX_OUT_OF_RANGE));
	g->map.arr[i] = (int *) malloc(sizeof(int) * g->map.width);
	if (!g->map.arr[i])
		return (errors_setter(g, ERR_MALLOC));
	s.j = -1;
	s.k = g->parsing.lowest_indent;
	while (++s.j < g->map.width)
	{
		if (line[s.k] && line[s.k] != '\n')
		{
			if (map_parse_helper(line, g, i, &s))
				return (RETURN_FAILURE);
		}
		else
			g->map.arr[i][s.j] = -1;
	}
	i++;
	return (RETURN_SUCCESS);
}
