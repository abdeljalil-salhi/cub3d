/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_pixel_put.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isalhi <isalhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 00:53:09 by absalhi           #+#    #+#             */
/*   Updated: 2023/05/18 18:20:37 by isalhi           ###   ########.fr       */
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
