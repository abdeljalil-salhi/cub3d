/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_map_norm.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 01:09:49 by absalhi           #+#    #+#             */
/*   Updated: 2023/05/21 05:36:54 by absalhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	is_invalid_eol(char *c)
{
	if (ft_strncmp(c, " \n", 2) == 0)
		return (true);
	return (false);
}

void	cub_map_init_norm(t_game *g, t_cub_map_init *s)
{
	g = (void *)g;
	s->it.i = 0;
	while (s->quick_line[s->it.i] && s->quick_line[s->it.i] == ' ')
		s->it.i++;
	s->it.j = s->it.i;
	while (s->quick_line[s->it.j]
		&& !is_invalid_eol(&s->quick_line[s->it.j])
		&& s->quick_line[s->it.j] != '\n')
		s->it.j++;
	if (s->it.j - s->it.i > s->width)
		s->width = s->it.j - s->it.i;
	if (s->lowest_indent == -1)
		s->lowest_indent = s->it.i;
	else if (s->it.i < s->lowest_indent)
		s->lowest_indent = s->it.i;
}
