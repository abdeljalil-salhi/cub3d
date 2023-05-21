/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_file_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 14:50:29 by absalhi           #+#    #+#             */
/*   Updated: 2023/05/21 05:35:24 by absalhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	cub_file_line_parse_identifier(t_game *g, char **line)
{
	if (ft_strncmp(line[0], "NO", 3) == 0)
		return (cub_parse_texture(g, line,
				&g->assets.north, &g->parsing.has_north));
	else if (ft_strncmp(line[0], "SO", 3) == 0)
		return (cub_parse_texture(g, line,
				&g->assets.south, &g->parsing.has_south));
	else if (ft_strncmp(line[0], "WE", 3) == 0)
		return (cub_parse_texture(g, line,
				&g->assets.west, &g->parsing.has_west));
	else if (ft_strncmp(line[0], "EA", 3) == 0)
		return (cub_parse_texture(g, line,
				&g->assets.east, &g->parsing.has_east));
	else if (ft_strncmp(line[0], "F", 2) == 0)
		return (cub_parse_color(g, line,
				&g->assets.floor, &g->parsing.has_floor));
	else if (ft_strncmp(line[0], "C", 2) == 0)
		return (cub_parse_color(g, line,
				&g->assets.ceiling, &g->parsing.has_ceiling));
	return (cub_errors_setter(g, MAP_INVALID_IDENTIFIER));
}

int	cub_parse_texture(t_game *g, char **line, char **t, bool *has_t)
{
	int	fd;

	if (*has_t)
		return (cub_errors_setter(g, MAP_DUPLICATE_IDENTIFIER));
	fd = -1;
	while (line[++fd])
		;
	if (fd != 2)
		return (cub_errors_setter(g, MAP_TEXTURE_UNKNOWN_ERROR));
	if (cub_file_open(g, &fd, line[1]))
		return (RETURN_FAILURE);
	close(fd);
	*t = ft_strdup(line[1]);
	*has_t = true;
	return (RETURN_SUCCESS);
}

typedef struct s_cub_parse_color
{
	char		**rgb;
	char		*join;
	char		*trim;
	char		*tmp;
	t_iterators	it;
}	t_cub_parse_color;

static int	cub_parse_color_joiner(t_cub_parse_color *s, t_game *g,
		char **line)
{
	s->join = ft_strdup("");
	if (!s->join)
		return (cub_errors_setter(g, ERR_MALLOC));
	s->it.i = -1;
	while (line[++s->it.i])
	{
		if (s->it.i == 0)
			continue ;
		else
		{
			s->tmp = s->join;
			s->join = ft_strjoin(s->join, line[s->it.i]);
			free(s->tmp);
		}
	}
	if (cub_count_occurences(s->join, ',') != 2)
		return (cub_errors_setter(g, MAP_INVALID_COLOR));
	s->rgb = ft_split(s->join, ",");
	free(s->join);
	if (!s->rgb)
		return (cub_errors_setter(g, ERR_MALLOC));
	return (RETURN_SUCCESS);
}

static int	cub_parse_color_helper(t_cub_parse_color *s, t_game *g)
{
	s->it.i = -1;
	while (s->rgb[++s->it.i])
		;
	if (s->it.i != 3)
		return (cub_errors_setter(g, MAP_INVALID_COLOR));
	s->it.i = -1;
	while (s->rgb[++s->it.i])
	{
		s->trim = ft_strtrim(s->rgb[s->it.i], " \t");
		if (!s->trim)
			return (cub_free_double_ptr((void **) s->rgb),
				cub_errors_setter(g, ERR_MALLOC));
		s->tmp = s->rgb[s->it.i];
		s->rgb[s->it.i] = s->trim;
		free(s->tmp);
		s->it.j = -1;
		while (s->rgb[s->it.i][++s->it.j])
			if (!ft_isdigit(s->rgb[s->it.i][s->it.j]))
				return (cub_free_double_ptr((void **) s->rgb),
					cub_errors_setter(g, MAP_INVALID_COLOR));
	}
	return (RETURN_SUCCESS);
}

int	cub_parse_color(t_game *g, char **line, t_color *c, bool *has_c)
{
	t_cub_parse_color	s;

	if (*has_c)
		return (cub_errors_setter(g, MAP_DUPLICATE_IDENTIFIER));
	if (cub_parse_color_joiner(&s, g, line))
		return (RETURN_FAILURE);
	if (cub_parse_color_helper(&s, g))
		return (RETURN_FAILURE);
	c->r = ft_atoi(s.rgb[0]);
	c->g = ft_atoi(s.rgb[1]);
	c->b = ft_atoi(s.rgb[2]);
	cub_free_double_ptr((void **) s.rgb);
	if (c->r < 0 || c->r > 255 || c->g < 0
		|| c->g > 255 || c->b < 0 || c->b > 255)
		return (cub_errors_setter(g, MAP_INVALID_COLOR_RANGE));
	*has_c = true;
	return (RETURN_SUCCESS);
}
