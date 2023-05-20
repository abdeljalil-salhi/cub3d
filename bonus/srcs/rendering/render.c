/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 00:58:36 by absalhi           #+#    #+#             */
/*   Updated: 2023/05/20 02:43:58 by absalhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_ray_rect(t_game *g, t_coords start, int width, int height, int color)
{
	t_iterators	it;
	int	used_color;
	it.i = -1;
	while (++it.i < height)
	{
		used_color = color;
		if (start.y + it.i >= g->win.height)
			break ;
		if (start.y + it.i < 0) 
			continue ;
		if (start.x >= g->win.width)
			break ;
		if (start.x < 0)
			continue ;
		if (it.i == 0 || it.i == height - 1)
			used_color = 0x000000;
		it.j = -1;
		while (++it.j < width)
			if (start.y + it.i < g->win.height && start.x + it.j < g->win.width)
				pixel_put(g, start.x + it.j, start.y + it.i, used_color);
	}
}

void	raycast(t_game *g)
{
	t_coords	origin;
	t_coords	map_pos;
	t_coords	horz_intersection;
	t_coords	vert_intersection;
	t_coords	horz_tile;
	t_coords	vert_tile;
	t_coords	distance;
	float		depth_horz;
	float		depth_vert;
	float		delta_depth;
	float		depth;
	float		ray_angle;
	float		sin_a, cos_a;
	int			vert_wall_content;
	int			horz_wall_content;
	t_iterators	it;

	origin = g->player.pos;
	map_pos.x = (int)(origin.x / TILE_SIZE);
	map_pos.y = (int)(origin.y / TILE_SIZE);
	ray_angle = g->player.angle - g->constants.half_fov + 0.0001;
	it.i = -1;
	while (++it.i < g->objects_count)
		g->objects[it.i].visible = false;
	it.i = -1;
	while (++it.i < NUM_RAYS)
	{
		g->rays[it.i].angle = ray_angle;

		sin_a = sin(ray_angle);
		cos_a = cos(ray_angle);
		
		horz_intersection.y = (sin_a > 0) ? (map_pos.y + 1) * TILE_SIZE : map_pos.y * TILE_SIZE - 0.0001;
		distance.y = (sin_a > 0) ? TILE_SIZE : -TILE_SIZE;
		
		depth_horz = (horz_intersection.y - origin.y) / sin_a;
		horz_intersection.x = origin.x + depth_horz * cos_a;

		delta_depth = distance.y / sin_a;
		distance.x = delta_depth * cos_a;
		
		it.j = -1;
		while (++it.j < MAX_DEPTH)
		{
			horz_tile.x = (int)(horz_intersection.x / TILE_SIZE);
			horz_tile.y = (int)(horz_intersection.y / TILE_SIZE);
			if (abs((int)(horz_tile.y)) >= g->map.height || abs((int)(horz_tile.x)) >= g->map.width)
				break ;
			if (it.i == (int) NUM_RAYS / 2)
				check_if_enemy(g, abs((int)(horz_tile.x)), abs((int)(horz_tile.y)));
			if (check_if_wall(g->map.arr[abs((int)(horz_tile.y))][abs((int)(horz_tile.x))]))
			{
				horz_wall_content = g->map.arr[abs((int)(horz_tile.y))][abs((int)(horz_tile.x))];
				break ;
			}
			horz_intersection.x += distance.x;
			horz_intersection.y += distance.y;
			depth_horz += delta_depth;
		}

		vert_intersection.x = (cos_a > 0) ? (map_pos.x + 1) * TILE_SIZE : map_pos.x * TILE_SIZE - 0.0001;
		distance.x = (cos_a > 0) ? TILE_SIZE : -TILE_SIZE;

		depth_vert = (vert_intersection.x - origin.x) / cos_a;
		vert_intersection.y = origin.y + depth_vert * sin_a;

		delta_depth = distance.x / cos_a;
		distance.y = delta_depth * sin_a;

		it.j = -1;
		while (++it.j < MAX_DEPTH)
		{
			vert_tile.x = (int)(vert_intersection.x / TILE_SIZE);
			vert_tile.y = (int)(vert_intersection.y / TILE_SIZE);
			if (abs((int)(vert_tile.y)) >= g->map.height || abs((int)(vert_tile.x)) >= g->map.width)
				break ;
			if (it.i == (int) NUM_RAYS / 2)
				check_if_enemy(g, abs((int)(vert_tile.x)), abs((int)(vert_tile.y)));
			if (check_if_wall(g->map.arr[abs((int)(vert_tile.y))][abs((int)(vert_tile.x))]))
			{
				vert_wall_content = g->map.arr[abs((int)(vert_tile.y))][abs((int)(vert_tile.x))];
				break ;
			}
			vert_intersection.x += distance.x;
			vert_intersection.y += distance.y;
			depth_vert += delta_depth;
		}

		if (depth_vert < depth_horz)
		{
			depth = depth_vert;
			vert_intersection.y = fmod(vert_intersection.y, TILE_SIZE);
			g->rays[it.i].depth = depth_vert;
			g->rays[it.i].wall_hit = vert_intersection;
			g->rays[it.i].content_hit = vert_wall_content;
			g->rays[it.i].vertical_hit = true;
		}
		else
		{
			depth = depth_horz;
			horz_intersection.x = fmod(horz_intersection.x, TILE_SIZE);
			g->rays[it.i].depth = depth_horz;
			g->rays[it.i].wall_hit = horz_intersection;
			g->rays[it.i].content_hit = horz_wall_content;
			g->rays[it.i].vertical_hit = false;
		}

		depth *= (float) cos(g->player.angle - ray_angle);
		float proj_height = (TILE_SIZE / depth) * g->constants.screen_dist;

		t_coords	start;
		t_coords	end;
		start = g->player.pos;
		end.x = start.x + depth * cos_a;
		end.y = start.y + depth * sin_a;
		
		int	wall_top_pixel;
		int	wall_bottom_pixel;
		int	text_offset_x;
		int	text_offset_y;
		int	i;
		unsigned int	textcolor;

		wall_top_pixel = g->constants.half_win_height - ((int) proj_height) / 2;
		wall_top_pixel = wall_top_pixel < 0 ? 0 : wall_top_pixel;
		wall_bottom_pixel = g->constants.half_win_height + ((int) proj_height) / 2;
		wall_bottom_pixel = wall_bottom_pixel > WIN_HEIGHT ? WIN_HEIGHT : wall_bottom_pixel;

		float		angle_r;
		float		cos_r;
		float		straight_dist;
		float		dist;
		t_coords	floor;
		t_coords	ceil;
		unsigned int floor_textcolor;
		unsigned int ceil_textcolor;

		angle_r =  g->player.angle - ray_angle;
		cos_r = cos(angle_r);
		i = -1;
		while (++i < wall_top_pixel)
		{
			straight_dist = g->constants.screen_dist * PLAYER_HEIGHT  /  (i - g->constants.half_win_height);
			dist = straight_dist / cos_r;
			ceil.x = g->player.pos.x - cos_a * dist;
			ceil.y = g->player.pos.y - sin_a * dist;
			text_offset_x = (int) ceil.x % TILE_SIZE;
			text_offset_y = (int) ceil.y % TILE_SIZE;
			ceil_textcolor = ((unsigned int *) g->textures.ceil.addr)[text_offset_y * TILE_SIZE + text_offset_x] & INJECTED_COLOR;
			pixel_put(g, it.i * g->constants.scale, i, ceil_textcolor);
		}
		if (g->rays[it.i].vertical_hit)
			text_offset_x = (int) vert_intersection.y;
		else
			text_offset_x = (int) horz_intersection.x;
		i = wall_top_pixel - 1;
		while (++i < wall_bottom_pixel)
		{
			text_offset_y = (i + (int) proj_height / 2 - g->constants.half_win_height) * (TILE_SIZE / proj_height);
			textcolor = ((unsigned int *) get_texture(g, it.i).addr)[(text_offset_y * TILE_SIZE) + text_offset_x] & INJECTED_COLOR;
			pixel_put(g, it.i * g->constants.scale, i, textcolor);
		}
		i--;
		while (++i < WIN_HEIGHT)
		{
			straight_dist = g->constants.screen_dist * PLAYER_HEIGHT  /  (i - g->constants.half_win_height);
			dist = straight_dist / cos_r;
			floor.x = g->player.pos.x + cos_a * dist;
			floor.y = g->player.pos.y + sin_a * dist;
			text_offset_x = (int) floor.x % TILE_SIZE;
			text_offset_y = (int) floor.y % TILE_SIZE;
			floor_textcolor = ((unsigned int *) g->textures.floor.addr)[text_offset_y * TILE_SIZE + text_offset_x] & INJECTED_COLOR;
			pixel_put(g, it.i * g->constants.scale, i, floor_textcolor);
		}
		ray_angle += g->constants.delta_angle;
		g->buffer[it.i] = depth;
	}
	render_sprite(g);
}

void	update(t_game *g)
{
	static float	ticks_last_frame = 0.0;

	if (ticks_last_frame < 0.5)
		ticks_last_frame = (float) current_time_ms();
	while ((float) current_time_ms() - (ticks_last_frame + g->constants.frame_rate) < 0)
		;
	g->delta_time = (float) (current_time_ms() - ticks_last_frame) / 1000.0f;
	ticks_last_frame = (float) current_time_ms();
}

int	render(t_game *g)
{
	static unsigned int	frames = 0;
	static unsigned int	last_fps = FPS;
	clock_t				elapsed_ticks;
	char				*fps_str;
	char				*tmp;

	g->frame.ref = mlx_new_image(g->mlx, g->win.width, g->win.height);
	g->frame.addr = mlx_get_data_addr(g->frame.ref, &g->frame.bpp, &g->frame.line_length, &g->frame.endian);
	frames++;
	elapsed_ticks = clock() - g->start_time;
	if (elapsed_ticks >= CLOCKS_PER_SEC)
	{
		last_fps = frames;
		frames = 0;
		g->start_time = clock();
	}
	if (g->mouse.enabled)
	{
		int	step_x, x, y;

		mlx_mouse_get_pos(g->win.ref, &x, &y);
		mlx_mouse_hide();
		if (x != g->mouse.x)
		{
			if (!g->paused)
			{
				step_x = x - g->mouse.x;
				g->mouse.angle = atan2(abs(step_x), WIN_WIDTH) * 180 / M_PI;
				if (step_x < 0)
					g->player.rotation_direction = -1;
				else if (step_x >= 0)
					g->player.rotation_direction = 1;
				g->mouse.x = x;
			}
			if ((g->mouse.x > WIN_WIDTH || g->mouse.x < 0) || g->paused)
			{
				g->mouse.x = WIN_WIDTH / 2;
				mlx_mouse_move(g->win.ref, WIN_WIDTH / 2, y);
			}
			if ((y > WIN_HEIGHT || y < 0) || g->paused)
				mlx_mouse_move(g->win.ref, x, WIN_HEIGHT / 2);
		}
		else
			g->player.rotation_direction = 0;
	}
	else
		mlx_mouse_show();
	update(g);
	player_movement(g);
	raycast(g);
	g->display_map ? draw_map(g) : draw_minimap(g);
	mlx_put_image_to_window(g->mlx, g->win.ref, g->frame.ref, 0, 0);
	if (!g->display_map)
		draw_weapon(g);
	put_tips(g);
	put_player_infos(g);
	put_upper_layer(g);
	mlx_destroy_image(g->mlx, g->frame.ref);
	tmp = ft_itoa(last_fps);
	fps_str = ft_strjoin("FPS: ", tmp);
	free(tmp);
	mlx_string_put(g->mlx, g->win.ref, 15, 70, 0xBB0000, fps_str);
	free(fps_str);
	return (RETURN_SUCCESS);
}
