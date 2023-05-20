/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 18:29:47 by absalhi           #+#    #+#             */
/*   Updated: 2023/05/20 00:22:12 by absalhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_interactive_objects(t_game *g, t_sprite_renderer *s)
{
	if (g->objects[s->z].type == OBJECT_MEDKIT && !check_for_medkits(g, s->z))
		return (RETURN_SUCCESS);
	else if (g->objects[s->z].type == OBJECT_WEAPON_SHOTGUN
		&& g->player.score > 100 && !check_for_weapon_drops(g, s->z))
		return (RETURN_SUCCESS);
	if (g->objects[s->z].type == OBJECT_DOOR)
		check_for_doors(g, s->z);
	if (is_enemy(g->objects[s->z].type))
		check_for_enemies(g, s->z);
	return (RETURN_DEFAULT);
}

static void	animate_objects(t_game *g, t_sprite_renderer *s)
{
	int	type;

	type = g->objects[s->z].type;
	if (type != OBJECT_DOOR
		&& !(is_enemy_dead(type) && g->objects[s->z].frame == 8))
	{
		if (g->textures.object_n_of_frames[type] > 1
			&& g->objects[s->z].frame == 0 && !g->objects[s->z].animating)
		{
			g->objects[s->z].animating = true;
			g->objects[s->z].last_time = current_time_ms();
		}
		if (current_time_ms() - g->objects[s->z].last_time
			> g->textures.object_frame_rate[type]
			&& g->objects[s->z].animating)
		{
			g->objects[s->z].frame++;
			g->objects[s->z].last_time = current_time_ms();
		}
		if (g->objects[s->z].frame == g->textures.object_n_of_frames[type]
			&& g->objects[s->z].animating)
			g->objects[s->z].frame = 0;
	}
}

static void	compute_angles(t_game *g, t_sprite_renderer *s)
{
	s->diff.x = g->objects[s->z].pos.x - g->player.pos.x;
	s->diff.y = g->objects[s->z].pos.y - g->player.pos.y;
	s->relative_angle = atan2(s->diff.y, s->diff.x);
	s->angle_sprite_player = g->player.angle - s->relative_angle;
	if (s->angle_sprite_player > M_PI)
		s->angle_sprite_player -= g->constants.tau;
	if (s->angle_sprite_player < -M_PI)
		s->angle_sprite_player += g->constants.tau;
	s->angle_sprite_player = fabs(s->angle_sprite_player);
}

static void	compute_calculations(t_game *g, t_sprite_renderer *s)
{
	s->dist = hypot(s->diff.x, s->diff.y) * cos(s->angle_sprite_player);
	s->sprite_height = (TILE_SIZE / s->dist) * g->constants.screen_dist
		* g->textures.object_scale[g->objects[s->z].type];
	s->sprite_width = s->sprite_height;
	s->ground_level = (TILE_SIZE / s->dist) * g->constants.screen_dist
		* (1 - g->textures.object_scale[g->objects[s->z].type]);
	s->sprite_top_y = g->constants.half_win_height - s->sprite_height
		/ 2 + s->ground_level;
	if (s->sprite_top_y < 0)
		s->sprite_top_y = 0;
	s->sprite_bottom_y = g->constants.half_win_height + s->sprite_height
		/ 2 + s->ground_level;
	if (s->sprite_bottom_y > WIN_HEIGHT)
		s->sprite_bottom_y = WIN_HEIGHT;
	s->sprite_angle = atan2(s->diff.y, s->diff.x) - g->player.angle;
	s->sprite_pos_x = tan(s->sprite_angle) * g->constants.screen_dist;
	s->sprite_left_x = g->constants.half_win_width + s->sprite_pos_x
		- s->sprite_width / 2;
	s->sprite_right_x = s->sprite_left_x + s->sprite_width;
}

int	render_sprite(t_game *g)
{
	t_sprite_renderer	s;

	compute_distances(g);
	sort_objects(g);
	s.z = -1;
	while (++s.z < g->objects_count)
	{
		if (!check_interactive_objects(g, &s))
			continue ;
		animate_objects(g, &s);
		compute_angles(g, &s);
		compute_calculations(g, &s);
		if (s.angle_sprite_player < g->constants.half_fov + 0.2)
			draw_sprite(g, &s);
	}
	return (RETURN_SUCCESS);
}
