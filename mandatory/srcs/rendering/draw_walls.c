/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 11:45:47 by absalhi           #+#    #+#             */
/*   Updated: 2023/05/20 00:41:16 by absalhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

unsigned int	get_textcolor(t_game *g, int type, t_iterators text_offset)
{
	int	ind;

	ind = (text_offset.i * TILE_SIZE) + text_offset.j;
	return (((unsigned int *) g->textures[type].addr)[ind]);
}

void	put_stripe(t_game *g, t_iterators it, t_iterators text_offset, int i)
{
	unsigned int	textcolor;

	if (g->rays[it.i].vertical_hit)
	{
		if (g->rays[it.i].horz_inters.x > g->player.pos.x)
			textcolor = get_textcolor(g, TEXT_E, text_offset);
		else
			textcolor = get_textcolor(g, TEXT_W, text_offset);
	}
	else
	{
		if (g->rays[it.i].vert_inters.y > g->player.pos.y)
			textcolor = get_textcolor(g, TEXT_S, text_offset);
		else
			textcolor = get_textcolor(g, TEXT_N, text_offset);
	}
	cub_pixel_put(g, it.i * g->constants.scale, i, textcolor);
}

void	draw_stripe(t_game *g, t_iterators it, int wall_top, int wall_bottom)
{
	t_iterators	text_offset;
	float		d;
	int			i;

	if (g->rays[it.i].vertical_hit)
		text_offset.j = (int) g->rays[it.i].vert_inters.y;
	else
		text_offset.j = (int) g->rays[it.i].horz_inters.x;
	d = TILE_SIZE / g->rays[it.i].proj_h;
	i = wall_top;
	while (i < wall_bottom)
	{
		text_offset.i = (i + (int) g->rays[it.i].proj_h / 2
				- g->constants.half_win_height) * d;
		put_stripe(g, it, text_offset, i);
		i++;
	}
}

typedef struct s_draw_walls
{
	int			i;
	int			wall_top_pixel;
	int			wall_bottom_pixel;
	float		depth;
}	t_draw_walls;

void	draw_walls(t_game *g, t_iterators it, float ray_angle)
{
	t_draw_walls	s;

	s.depth = g->rays[it.i].depth * (float) cos(g->player.angle - ray_angle);
	g->rays[it.i].proj_h = (TILE_SIZE / s.depth) * g->constants.screen_dist;
	s.wall_top_pixel
		= g->constants.half_win_height - (int) g->rays[it.i].proj_h / 2;
	if (s.wall_top_pixel < 0)
		s.wall_top_pixel = 0;
	s.wall_bottom_pixel
		= g->constants.half_win_height + (int) g->rays[it.i].proj_h / 2;
	if (s.wall_bottom_pixel > WIN_HEIGHT)
		s.wall_bottom_pixel = WIN_HEIGHT;
	s.i = -1;
	while (++s.i < s.wall_top_pixel)
		cub_pixel_put(g,
			it.i * g->constants.scale, s.i, create_rgb(g->assets.ceiling));
	draw_stripe(g, it, s.wall_top_pixel, s.wall_bottom_pixel);
	s.i = s.wall_bottom_pixel - 1;
	while (++s.i < WIN_HEIGHT)
		cub_pixel_put(g,
			it.i * g->constants.scale, s.i, create_rgb(g->assets.floor));
}
