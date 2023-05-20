/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 01:16:49 by absalhi           #+#    #+#             */
/*   Updated: 2023/05/20 01:17:10 by absalhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

t_image	get_texture(t_game *g, int ind)
{
	if (g->rays[ind].content_hit >= 1 && g->rays[ind].content_hit <= 5)
		return (g->textures.walls[g->rays[ind].content_hit - 1]);
	return (g->textures.walls[0]);
}
