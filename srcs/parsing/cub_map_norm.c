/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_map_norm.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 01:09:49 by absalhi           #+#    #+#             */
/*   Updated: 2023/03/24 01:13:26 by absalhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	cub_map_init_norm(t_cub_map_init *s)
{
	s->it.i = 0;
	while (s->quick_line[s->it.i] && s->quick_line[s->it.i] == ' ')
		s->it.i++;
	s->it.j = s->it.i;
	while (s->quick_line[s->it.j]
		&& s->quick_line[s->it.j] != ' ' && s->quick_line[s->it.j] != '\n')
		s->it.j++;
	if (s->it.j - s->it.i > s->width)
		s->width = s->it.j - s->it.i;
	if (s->lowest_indent == -1)
		s->lowest_indent = s->it.i;
	else if (s->it.i < s->lowest_indent)
		s->lowest_indent = s->it.i;
}
