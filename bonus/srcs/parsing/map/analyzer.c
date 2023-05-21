/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyzer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 01:09:49 by absalhi           #+#    #+#             */
/*   Updated: 2023/05/21 05:29:57 by absalhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	is_object(char c)
{
	return (c == 'B' || c == 'L' || c == 'P' || c == 'G' || c == 'M'
		|| c == 'D' || c == 'V' || c == 'C' || c == 'H' || c == 'K');
}

static bool	is_invalid_eol(char *c)
{
	if (ft_strncmp(c, " \n", 2) == 0)
		return (true);
	return (false);
}

void	map_analyzer(t_game *g, t_parsing_analyzer *s)
{
	s->it.i = 0;
	while (s->quick_line[s->it.i] && s->quick_line[s->it.i] == ' ')
		s->it.i++;
	s->it.j = s->it.i;
	while (s->quick_line[s->it.j]
		&& !is_invalid_eol(&s->quick_line[s->it.j])
		&& s->quick_line[s->it.j] != '\n')
	{
		if (is_object(s->quick_line[s->it.j]))
			g->objects_count++;
		s->it.j++;
	}
	if (s->it.j - s->it.i > s->width)
		s->width = s->it.j - s->it.i;
	if (s->lowest_indent == -1)
		s->lowest_indent = s->it.i;
	else if (s->it.i < s->lowest_indent)
		s->lowest_indent = s->it.i;
}
