/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 21:28:45 by absalhi           #+#    #+#             */
/*   Updated: 2023/05/17 22:59:24 by absalhi          ###   ########.fr       */
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
	g->objects = (t_object *) malloc(sizeof(t_object) * g->objects_count);
	if (!g->objects)
		return (cub_errors_setter(g, ERR_MALLOC));
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
		cub_map_init_norm(g, &s);
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
		int i, int j, float degree)
{
	g->map.arr[i][j] = PLAYER;
	g->player.pos.x = TILE_SIZE * j + TILE_SIZE / 2;
	g->player.pos.y = TILE_SIZE * i + TILE_SIZE / 2;
	g->player.width = PLAYER_WIDTH;
	g->player.height = PLAYER_HEIGHT;
	g->player.angle = degree;
	g->player.speed = PLAYER_SPEED;
	g->player.rot_speed = PLAYER_ROTATION_SPEED;
}

bool	is_object(char c)
{
	return (c == 'B' || c == 'L' || c == 'P' || c == 'G'
		|| c == 'M' || c == 'D' || c == 'V' || c == 'C'
		|| c == 'H');
}

void	cub_parse_object(t_game *g, char c, int i, int j)
{
	static int	count = 0;

	g->map.arr[i][j] = 0;
	g->objects[count].state = 0;
	g->objects[count].infos[ENEMY_HEALTH] = 1;
	if (c == 'B')
		g->objects[count].type = OBJECT_BARREL;
	else if (c == 'P')
		g->objects[count].type = OBJECT_PILLAR;
	else if (c == 'L')
		g->objects[count].type = OBJECT_LAMP;
	else if (c == 'G')
		g->objects[count].type = OBJECT_GREEN_LIGHT;
	else if (c == 'M')
		g->objects[count].type = OBJECT_MEDKIT;
	else if (c == 'D')
	{
		g->map.arr[i][j] = DOOR_CLOSED;
		g->objects[count].type = OBJECT_DOOR;
		g->objects[count].state = DOOR_CLOSED;
	}
	else if (c == 'V')
	{
		g->objects[count].type = OBJECT_SOLDIER_WALK;
		g->objects[count].infos[ENEMY_HEALTH] = 50;
		g->objects[count].infos[ENEMY_BOUNTY] = 100;
		g->objects[count].infos[ENEMY_PRECISION] = 20;
		g->objects[count].infos[ENEMY_DAMAGE] = 10;
		g->objects[count].infos[ENEMY_RANGE] = 200;
		g->objects[count].infos[ENEMY_SPEED] = 150;
	}
	else if (c == 'C')
	{
		g->objects[count].type = OBJECT_CYBERDEMON_WALK;
		g->objects[count].infos[ENEMY_HEALTH] = 200;
		g->objects[count].infos[ENEMY_BOUNTY] = 500;
		g->objects[count].infos[ENEMY_PRECISION] = 30;
		g->objects[count].infos[ENEMY_DAMAGE] = 30;
		g->objects[count].infos[ENEMY_RANGE] = 500;
		g->objects[count].infos[ENEMY_SPEED] = 70;
	}
	else if (c == 'H')
		g->objects[count].type = OBJECT_WEAPON_SHOTGUN;
	g->objects[count].pos.x = j * TILE_SIZE + TILE_SIZE / 2;
	g->objects[count].pos.y = i * TILE_SIZE + TILE_SIZE / 2;
	g->objects[count].frame = 0;
	g->objects[count].animating = false;
	g->objects[count].visible = false;
	g->objects[count].display = true;
	count++;
}

static int	cub_map_parse_helper(char *line, t_game *g,
		int i, t_cub_map_parse *s)
{
	if (line[s->k] == ' ')
		g->map.arr[i][s->j] = -1;
	else if (line[s->k] >= '0' && line[s->k] <= '5')
		g->map.arr[i][s->j] = line[s->k] - 48;
	else if (line[s->k] == 'N')
		cub_map_parse_helper_setter(g, i, s->j, 3 * M_PI / 2);
	else if (line[s->k] == 'S')
		cub_map_parse_helper_setter(g, i, s->j, M_PI / 2);
	else if (line[s->k] == 'E')
		cub_map_parse_helper_setter(g, i, s->j, 2 * M_PI);
	else if (line[s->k] == 'W')
		cub_map_parse_helper_setter(g, i, s->j, M_PI);
	else if (is_object(line[s->k]))
		cub_parse_object(g, line[s->k], i, s->j);
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
