/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_pixel_put.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 00:53:09 by absalhi           #+#    #+#             */
/*   Updated: 2023/03/27 06:28:47 by absalhi          ###   ########.fr       */
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

	it.i = -1;
	while (++it.i < size)
	{
		it.j = -1;
		while (++it.j < size)
		{
			if (pos.i * size + it.i < g->win.height && pos.j * size + it.j < g->win.width
				&& (it.i == 0 || it.i == size - 1 || it.j == 0 || it.j == size - 1))
				cub_pixel_put(g, size * pos.j + it.j, size * pos.i + it.i, color);
		}
	}
}
