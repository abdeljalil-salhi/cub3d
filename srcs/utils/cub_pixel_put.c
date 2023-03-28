/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_pixel_put.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 00:53:09 by absalhi           #+#    #+#             */
/*   Updated: 2023/03/28 02:23:03 by absalhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	cub_pixel_put(t_game *g, int x, int y, int color)
{
	t_image	*image;
	char	*dst;

	image = &g->frame;
	dst = image->addr + (y * image->line_length + x * (image->bpp / 8));
	*(unsigned int *)dst = color;
}

void	cub_rect_put(t_game *g, t_iterators pos, int color, int size)
{
	t_iterators	it;
	int			horizontal_size;
	int			vertical_size;

	(void) size;
	vertical_size = g->win.width / g->map.width;
	horizontal_size = g->win.height / g->map.height;
	it.i = -1;
	while (++it.i < horizontal_size)
	{
		it.j = -1;
		while (++it.j < vertical_size)
			if (pos.i * horizontal_size + it.i < g->win.height && pos.j * vertical_size + it.j < g->win.width
				&& (it.i == 0 || it.i == horizontal_size - 1 || it.j == 0 || it.j == vertical_size - 1))
				cub_pixel_put(g, vertical_size * pos.j + it.j, horizontal_size * pos.i + it.i + 1, color);
	}
}
