/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_file_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 14:50:29 by absalhi           #+#    #+#             */
/*   Updated: 2023/03/21 11:07:16 by absalhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	cub_file_line_empty(char *line)
{
	int	i;

	i = -1;
	while (line[++i] == 32 || (line[i] >= 9 && line[i] <= 13))
		;
	if (line[i] == '\0' || line[i] == '\n')
		return (true);
	return (false);
}

int	cub_file_line_parse_identifier(t_game *g, char **line)
{
	if (ft_strncmp(line[0], "NO", 2) == 0)
		return (cub_parse_texture(g, line, &g->assets.north, &g->parsing.has_north));
	else if (ft_strncmp(line[0], "SO", 2) == 0)
		return (cub_parse_texture(g, line, &g->assets.south, &g->parsing.has_south));
	else if (ft_strncmp(line[0], "WE", 2) == 0)
		return (cub_parse_texture(g, line, &g->assets.west, &g->parsing.has_west));
	else if (ft_strncmp(line[0], "EA", 2) == 0)
		return (cub_parse_texture(g, line, &g->assets.east, &g->parsing.has_east));
	else if (ft_strncmp(line[0], "F", 1) == 0)
		return (cub_parse_color(g, line, &g->assets.floor, &g->parsing.has_floor));
	else if (ft_strncmp(line[0], "C", 1) == 0)
		return (cub_parse_color(g, line, &g->assets.ceiling, &g->parsing.has_ceiling));
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
	fd = open(line[1], O_RDONLY);
	if (fd == -1)
	{
		if (errno == EACCES)
			return (cub_errors_setter(g, MAP_TEXTURE_PERMISSION));
		else if (errno == ENOENT)
			return (cub_errors_setter(g, MAP_TEXTURE_NOT_FOUND));
		else
			return (cub_errors_setter(g, MAP_TEXTURE_UNKNOWN_ERROR));
	}
	close(fd);
	*t = line[1];
	*has_t = true;
	return (RETURN_SUCCESS);
}

int	cub_parse_color(t_game *g, char **line, t_color *c, bool *has_c)
{
	char	**rgb;
	char	*join;
	char	*trim;
	char	*tmp;
	int		i;
	int		j;

	if (*has_c)
		return (cub_errors_setter(g, MAP_DUPLICATE_IDENTIFIER));
	join = ft_strdup("");
	if (!join)
		return (cub_errors_setter(g, ERR_MALLOC));
	i = -1;
	while (line[++i])
	{
		if (i == 0)
			continue ;
		else
		{
			tmp = join;
			join = ft_strjoin(join, line[i]);
			free(tmp);
		}
	}
	rgb = ft_split(join, ",");
	free(join);
	if (!rgb)
		return (cub_errors_setter(g, ERR_MALLOC));
	i = -1;
	while (rgb[++i])
		;
	if (i != 3)
		return (cub_errors_setter(g, MAP_INVALID_COLOR));
	i = -1;
	while (rgb[++i])
	{
		trim = ft_strtrim(rgb[i], " \t");
		if (!trim)
			return (cub_free_double_ptr((void **) rgb),
				cub_errors_setter(g, ERR_MALLOC));
		tmp = rgb[i];
		rgb[i] = trim;
		free(tmp);
		j = -1;
		while (rgb[i][++j])
			if (!ft_isdigit(rgb[i][j]))
				return (cub_free_double_ptr((void **) rgb),
					cub_errors_setter(g, MAP_INVALID_COLOR));
	}
	c->r = ft_atoi(rgb[0]);
	c->g = ft_atoi(rgb[1]);
	c->b = ft_atoi(rgb[2]);
	cub_free_double_ptr((void **) rgb);
	if (c->r < 0 || c->r > 255 || c->g < 0 || c->g > 255 || c->b < 0 || c->b > 255)
		return (cub_errors_setter(g, MAP_INVALID_COLOR_RANGE));
	*has_c = true;
	return (RETURN_SUCCESS);
}
