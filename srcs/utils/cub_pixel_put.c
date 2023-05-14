/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_pixel_put.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 00:53:09 by absalhi           #+#    #+#             */
/*   Updated: 2023/05/13 20:34:33 by absalhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	cub_pixel_put(t_game *g, float x, float y, int color)
{
	t_image	*image;
	char	*dst;
	int		int_x;
	int		int_y;

	image = &g->frame;
	int_x = (int)round(x);
	int_y = (int)round(y);
	if (x < 0 || x > g->win.width || y < 0 || y > g->win.height)
		return ;
	dst = image->addr + (int_y * image->line_length
			+ int_x * (image->bpp / 8));
	*(unsigned int *)dst = color;
}

void	cub_rect_put(t_game *g, t_iterators pos, int color)
{
	t_iterators	it;

	it.i = -1;
	while (++it.i < TILE_SIZE)
	{
		it.j = -1;
		while (++it.j < TILE_SIZE)
			if (pos.i * TILE_SIZE + it.i < g->win.height
				&& pos.j * TILE_SIZE + it.j < g->win.width
				&& (it.i == 0 || it.i == TILE_SIZE - 1
					|| it.j == 0 || it.j == TILE_SIZE - 1))
				cub_pixel_put(g, TILE_SIZE * pos.j + it.j,
					TILE_SIZE * pos.i + it.i + 1, color);
	}
}

void	draw_rect(t_game *g, t_iterators pos, int width, int height, int color)
{
	t_iterators	it;

	it.i = -1;
	while (++it.i < height)
	{
		it.j = -1;
		while (++it.j < width)
			cub_pixel_put(g, pos.j + it.j, pos.i + it.i, color);
	}
}
