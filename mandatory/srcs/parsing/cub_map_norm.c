/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_map_norm.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isalhi <isalhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 01:09:49 by absalhi           #+#    #+#             */
/*   Updated: 2023/05/18 01:53:32 by isalhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	cub_map_init_norm(t_game *g, t_cub_map_init *s)
{
	g = (void *)g;
	s->it.i = 0;
	while (s->quick_line[s->it.i] && s->quick_line[s->it.i] == ' ')
		s->it.i++;
	s->it.j = s->it.i;
	while (s->quick_line[s->it.j]
		&& s->quick_line[s->it.j] != ' ' && s->quick_line[s->it.j] != '\n')
	{
		s->it.j++;
	}
	if (s->it.j - s->it.i > s->width)
		s->width = s->it.j - s->it.i;
	if (s->lowest_indent == -1)
		s->lowest_indent = s->it.i;
	else if (s->it.i < s->lowest_indent)
		s->lowest_indent = s->it.i;
}
