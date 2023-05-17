/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_renderer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 18:29:47 by absalhi           #+#    #+#             */
/*   Updated: 2023/05/17 00:53:49 by absalhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define COLOR 0xFFFFFF

void	compute_distances(t_game *g)
{
	int	i;

	i = -1;
	while (++i < g->objects_count)
		g->objects[i].dist = hypot(g->objects[i].pos.x - g->player.pos.x, g->objects[i].pos.y - g->player.pos.y);
}

void	sort_objects(t_game *g)
{
	t_iterators	it;
	t_object	temp;
	
	it.i = 0;
	while (it.i < g->objects_count)
	{
		it.j = it.i + 1;
		while (it.j < g->objects_count)
		{
			if (g->objects[it.j].dist > g->objects[it.i].dist)
			{
				temp.dist = g->objects[it.j].dist;
				temp.animating = g->objects[it.j].animating;
				temp.frame = g->objects[it.j].frame;
				temp.pos = g->objects[it.j].pos;
				temp.type = g->objects[it.j].type;
				temp.last_time = g->objects[it.j].last_time;
				temp.display = g->objects[it.j].display;
				temp.x = g->objects[it.j].x;
				temp.y = g->objects[it.j].y;
				temp.state = g->objects[it.j].state;

				g->objects[it.j].dist = g->objects[it.i].dist;
				g->objects[it.j].animating = g->objects[it.i].animating;
				g->objects[it.j].frame = g->objects[it.i].frame;
				g->objects[it.j].pos = g->objects[it.i].pos;
				g->objects[it.j].type = g->objects[it.i].type;
				g->objects[it.j].last_time = g->objects[it.i].last_time;
				g->objects[it.j].display = g->objects[it.i].display;
				g->objects[it.j].x = g->objects[it.i].x;
				g->objects[it.j].y = g->objects[it.i].y;
				g->objects[it.j].state = g->objects[it.i].state;

				g->objects[it.i].dist = temp.dist;
				g->objects[it.i].animating = temp.animating;
				g->objects[it.i].frame = temp.frame;
				g->objects[it.i].pos = temp.pos;
				g->objects[it.i].type = temp.type;
				g->objects[it.i].last_time = temp.last_time;
				g->objects[it.i].display = temp.display;
				g->objects[it.i].x = temp.x;
				g->objects[it.i].y = temp.y;
				g->objects[it.i].state = temp.state;
			}
			it.j++;
		}
		it.i++;
	}
}

bool	check_for_medkits(t_game *g, int z);
void	check_for_doors(t_game *g, int z);
int	cub_render_sprite(t_game *g)
{
	float			angle_sprite_player;
	float			relative_angle;
	float			sprite_height, sprite_width;
	float			dist;
	float			sprite_bottom_y, sprite_top_y, sprite_left_x, sprite_right_x;
	float			sprite_angle;
	float			sprite_pos_x;
	int				text_x, text_y, i, j;
	unsigned int	color;
	t_coords		diff;
	int				z;

	compute_distances(g);
	sort_objects(g);
	z = -1;
	while (++z < g->objects_count)
	{
		if (g->objects[z].type == OBJECT_MEDKIT && !check_for_medkits(g, z))
			continue ;
		if (g->objects[z].type == OBJECT_DOOR)
			check_for_doors(g, z);

		if (g->objects[z].type != OBJECT_DOOR)
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
		}

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
						color = ((unsigned int *) g->textures.object_image[g->objects[z].type][g->objects[z].frame].addr)[text_y * TILE_SIZE + text_x] & COLOR;
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
