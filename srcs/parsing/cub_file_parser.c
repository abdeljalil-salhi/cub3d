/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_file_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 23:27:34 by absalhi           #+#    #+#             */
/*   Updated: 2023/03/24 00:20:58 by absalhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	cub_file_parser(t_game *g)
{
	if (cub_check_disponibility(g))
		return (RETURN_FAILURE);
	if (cub_check_extension(g))
		return (RETURN_FAILURE);
	if (cub_parse_config(g))
		return (RETURN_FAILURE);
	return (RETURN_SUCCESS);
}

int	cub_parse_config(t_game *g)
{
	char	*line;

	while (true)
	{
		line = get_next_line(g->map.file.fd);
		if (!line)
			break ;
		if (cub_line_empty(line))
		{
			if (g->parsing.map_initialized)
				return (cub_free(line), cub_errors_setter(g, MAP_EMPTY_LINE));
			cub_map_check(g, line);
			cub_free(line);
			continue ;
		}
		cub_map_check(g, line);
		if (cub_file_line_parse(g, line))
			return (cub_free(line), RETURN_FAILURE);
		free(line);
	}
	return (RETURN_SUCCESS);
}

int	cub_file_line_parse(t_game *g, char *line)
{
	char	**split;

	if (g->parsing.is_map)
		return (cub_map_parse(g, line));
	line[ft_strlen(line) - 1] = 0;
	split = ft_split(line, " \t\n");
	if (!split)
		return (cub_errors_setter(g, ERR_MALLOC));
	if (cub_file_line_parse_identifier(g, split))
		return (cub_free_double_ptr((void **) split), RETURN_FAILURE);
	cub_free_double_ptr((void **) split);
	return (RETURN_SUCCESS);
}
