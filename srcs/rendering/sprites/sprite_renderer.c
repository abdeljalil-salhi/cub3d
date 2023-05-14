/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_renderer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 18:29:47 by absalhi           #+#    #+#             */
/*   Updated: 2023/05/14 21:29:40 by absalhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	cub_render_sprite(t_game *g)
{
	float	angle_sprite_player;
	float	relative_angle;
	float	sprite_height, sprite_width;
	float	dist;
	float	sprite_bottom_y, sprite_top_y, sprite_left_x, sprite_right_x;
	float	sprite_angle;
	float	sprite_pos_x;
	int		text_x, text_y, i, j;
	unsigned int	color;
	t_coords	diff;
	int		z;

	z = -1;
	while (++z < g->objects_count)
	{
		if (g->textures.object_n_of_frames[g->objects[z].type] > 1
			&& g->objects[z].frame == 0 && !g->objects[z].animating)
		{
			g->objects[z].animating = true;
			g->objects[z].last_time = current_time_ms();
		}
		if (current_time_ms() - g->objects[z].last_time
			> g->textures.object_frame_rate[g->objects[z].type])
		{
			g->objects[z].frame++;
			g->objects[z].last_time = current_time_ms();
		}
		if (g->objects[z].frame == g->textures.object_n_of_frames[g->objects[z].type])
			g->objects[z].frame = 0;
		diff.x = g->objects[z].pos.x - g->player.pos.x;
		diff.y = g->objects[z].pos.y - g->player.pos.y;

		relative_angle = atan2(diff.y, diff.x);

		angle_sprite_player = g->player.angle - relative_angle;

		if (angle_sprite_player > M_PI)
			angle_sprite_player -= TAU;
		if (angle_sprite_player < -M_PI)
			angle_sprite_player += TAU;

		angle_sprite_player = fabs(angle_sprite_player);

		if (angle_sprite_player < HALF_FOV + 0.2)
		{
			dist = hypot(diff.x, diff.y) * cos(angle_sprite_player);

			sprite_height = (TILE_SIZE / dist) * SCREEN_DIST * g->textures.object_scale[g->objects[z].type];
			sprite_width = sprite_height;

			sprite_top_y = HALF_WIN_HEIGHT - sprite_height / 2;
			if (sprite_top_y < 0) sprite_top_y = 0;
			sprite_bottom_y = HALF_WIN_HEIGHT + sprite_height / 2;
			if (sprite_bottom_y > WIN_HEIGHT) sprite_bottom_y = WIN_HEIGHT;

			sprite_angle = atan2(diff.y, diff.x) - g->player.angle;
			sprite_pos_x = tan(sprite_angle) * SCREEN_DIST;

			sprite_left_x = HALF_WIN_WIDTH + sprite_pos_x - sprite_width / 2;
			sprite_right_x = sprite_left_x + sprite_width;

			i = sprite_left_x;
			while (i < sprite_right_x)
			{
				text_x = (i - sprite_left_x) * (TILE_SIZE / sprite_width);
				j = sprite_top_y;
				while (j < sprite_bottom_y)
				{
					if (i > 0 && i < WIN_WIDTH && j > 0 && j < WIN_HEIGHT)
					{
						text_y = (j + sprite_height / 2 - HALF_WIN_HEIGHT) * (TILE_SIZE / sprite_height);
						color = ((unsigned int *) g->textures.object_image[g->objects[z].type][g->objects[z].frame].addr)[text_y * TILE_SIZE + text_x];
					if ((color  & 0xFFFF00FF) != 0 && dist < g->buffer[i])
							cub_pixel_put(g, i * SCALE, j, color);
					}
					j++;
				}
				i++;
			}
		}
	}
	return (RETURN_SUCCESS);
}
