/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 01:25:18 by absalhi           #+#    #+#             */
/*   Updated: 2023/05/20 02:24:39 by absalhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	player_movement(t_game *g)
{
	t_coords	diff;
	float		speed;
	float		speed_sin;
	float		speed_cos;

	diff.x = 0;
	diff.y = 0;
	speed = g->player.speed * g->delta_time;
	speed_sin = speed * sin(g->player.angle);
	speed_cos = speed * cos(g->player.angle);
	diff.x += -speed_cos * g->player.walk_direction;
	diff.y += -speed_sin * g->player.walk_direction;
	diff.x += -speed_sin * g->player.turn_direction;
	diff.y += speed_cos * g->player.turn_direction;
	check_wall_collision(g, diff.x, diff.y);
	if (!g->paused)
	{
		g->player.angle += g->mouse.angle * g->delta_time
			* g->player.rotation_direction;
		g->player.angle = fmod(g->player.angle, g->constants.tau);
	}
	return (RETURN_SUCCESS);
}
