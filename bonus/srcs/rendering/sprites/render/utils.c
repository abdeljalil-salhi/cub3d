/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 11:11:57 by absalhi           #+#    #+#             */
/*   Updated: 2023/05/20 00:12:55 by absalhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static unsigned int	get_color(t_game *g,
		int type, int frame, t_sprite_renderer *s)
{
	return (((unsigned int *) g->textures.object_image[type][frame].addr)
			[s->text_y * TILE_SIZE + s->text_x] & INJECTED_COLOR);
}

static int	get_y_texture(t_game *g, t_sprite_renderer *s)
{
	return ((s->j - s->ground_level + s->sprite_height / 2
			- g->constants.half_win_height) * (TILE_SIZE / s->sprite_height));
}

void	compute_distances(t_game *g)
{
	int	i;
	int	x;
	int	y;

	i = -1;
	while (++i < g->objects_count)
	{
		x = g->objects[i].pos.x - g->player.pos.x;
		y = g->objects[i].pos.y - g->player.pos.y;
		g->objects[i].dist = hypot(x, y);
	}
}

void	draw_sprite(t_game *g, t_sprite_renderer *s)
{
	s->i = s->sprite_left_x - 1;
	while (++s->i < s->sprite_right_x)
	{
		s->text_x = (s->i - s->sprite_left_x) * (TILE_SIZE / s->sprite_width);
		s->j = s->sprite_top_y - 1;
		while (++s->j < s->sprite_bottom_y)
		{
			if (s->i > 0 && s->i < WIN_WIDTH && s->j > 0 && s->j < WIN_HEIGHT)
			{
				s->text_y = get_y_texture(g, s);
				s->color = get_color(g,
						g->objects[s->z].type, g->objects[s->z].frame, s);
				if ((s->color & 0xFFFF00FF) != 0 && s->dist < g->buffer[s->i])
					pixel_put(g, s->i * g->constants.scale, s->j, s->color);
			}
		}
	}
}
