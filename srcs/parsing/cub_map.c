/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 21:28:45 by absalhi           #+#    #+#             */
/*   Updated: 2023/03/22 14:42:00 by absalhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	cub_map_init(t_game *g)
{
	int		i;
	int		j;
	int		lowest_indent;
	char	*quick_line;
	int		width;
	int		height;

	lowest_indent = -1;
	width = 0;
	height = 0;
	close(g->map.file.fd);
	g->map.file.fd = open(g->map.file.path, O_RDONLY);
	i = -1;
	while (++i < g->parsing.lines_before_map)
		free(get_next_line(g->map.file.fd));
	while (true)
	{
		quick_line = get_next_line(g->map.file.fd);
		if (!quick_line)
			break ;
		printf(GREEN "%s" RESET, quick_line);
		if (cub_file_line_empty(quick_line))
		{
			free(quick_line);
			continue ;
		}
		i = 0;
		while (quick_line[i] && quick_line[i] == ' ')
			i++;
		j = 0;
		while (quick_line[j] && quick_line[i] != ' ' && quick_line[i] != '\n')
			j++;
		if (j > width)
			width = j;
		if (lowest_indent == -1)
			lowest_indent = i;
		else if (i < lowest_indent)
			lowest_indent = i;
		height++;
		free(quick_line);
	}
	g->parsing.lowest_indent = lowest_indent;
	g->map.width = width;
	g->map.height = height;
	close(g->map.file.fd);
	g->map.file.fd = open(g->map.file.path, O_RDONLY);
	if (g->map.file.fd == -1)
	{
		if (errno == EACCES)
			return (cub_errors_setter(g, FILE_PERMISSION_DENIED));
		else if (errno == ENOENT)
			return (cub_errors_setter(g, FILE_NOT_FOUND));
		else
			return (cub_errors_setter(g, FILE_UNKNOWN_ERROR));
	}
	i = -1;
	while (++i < g->parsing.lines_before_map)
		free(get_next_line(g->map.file.fd));
	g->map.arr = (int **) malloc(sizeof(int *) * g->map.height);
	if (!g->map.arr)
		return (cub_errors_setter(g, ERR_MALLOC));
	g->parsing.map_initialized = true;
	return (RETURN_SUCCESS);
}

int	cub_map_parse(t_game *g, char *line)
{
	static int	i = -1;
	int			j;
	int			k;

	if (!g->parsing.map_initialized)
		if (cub_map_init(g))
			return (RETURN_FAILURE);
	if (++i >= g->map.height)
		return (cub_errors_setter(g, MAP_INDEX_OUT_OF_RANGE));
	g->map.arr[i] = (int *) malloc(sizeof(int) * g->map.width);
	if (!g->map.arr[i])
		return (cub_errors_setter(g, ERR_MALLOC));
	j = -1;
	k = g->parsing.lowest_indent;
	while (++j < g->map.width)
	{
		if (line[k] && line[k] != '\n')
		{
			if (line[k] == ' ')
				g->map.arr[i][j] = -1;
			else if (line[k] == '0')
				g->map.arr[i][j] = 0;
			else if (line[k] == '1')
				g->map.arr[i][j] = 1;
			else if (line[k] == 'N')
			{
				g->map.arr[i][j] = 2;
				g->player.degree = 270;
			}
			else if (line[k] == 'S')
			{
				g->map.arr[i][j] = 2;
				g->player.degree = 90;
			}
			else if (line[k] == 'E')
			{
				g->map.arr[i][j] = 2;
				g->player.degree = 0;
			}
			else if (line[k] == 'W')
			{
				g->map.arr[i][j] = 2;
				g->player.degree = 180;
			}
			else
				return (cub_errors_setter(g, MAP_INVALID_CHAR));
			k++;
		}
		else
			g->map.arr[i][j] = -1;
	}
	return (RETURN_SUCCESS);
}

int	cub_map_check(t_game *g, char *line)
{
	static unsigned int	lines_before_map = 0;

	if (g->parsing.has_north && g->parsing.has_south && g->parsing.has_west
		&& g->parsing.has_east && g->parsing.has_floor && g->parsing.has_ceiling
		&& !cub_file_line_empty(line) && !g->parsing.is_map)
	{
		g->parsing.is_map = true;
		g->parsing.lines_before_map = lines_before_map;
	}
	if (!g->parsing.map_initialized)
		lines_before_map++;
	return (RETURN_SUCCESS);
}
