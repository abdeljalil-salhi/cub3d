/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_render.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 00:58:36 by absalhi           #+#    #+#             */
/*   Updated: 2023/03/31 06:49:59 by absalhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	display_map(t_game *g)
{
	t_iterators	it;

	it.i = -1;
	while (++it.i < g->map.height)
	{
		it.j = -1;
		while (++it.j < g->map.width)
			if (g->map.arr[it.i][it.j] == 1)
				cub_rect_put(g, it, 0xFFFFFF);
	}
}

void	draw_line(t_game *g, t_coords start, t_coords end)
{
    int dx = end.x - start.x;
    int dy = end.y - start.y;
    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
    float xinc = dx / (float)steps;
    float yinc = dy / (float)steps;
    float x = start.x;
    float y = start.y;
    for (int i = 0; i <= steps; i++) 
    {
        cub_pixel_put(g, round(x), round(y), 0xFF0000);
        x += xinc;
        y += yinc;
    }
}

void	draw_player(t_game *g)
{
	t_iterators	it;
	t_coords	pos;
	t_coords	end_pos;

	pos.y = g->player.pos.y - g->player.height / 2;
	pos.x = g->player.pos.x - g->player.width / 2;
	it.i = -1;
	while (++it.i < g->player.height)
	{
		it.j = -1;
		while (++it.j < g->player.width)
			if (pos.y + it.i < g->win.height && pos.x + it.j < g->win.width)
				cub_pixel_put(g, pos.x + it.j, pos.y + it.i, 0xFF0000);
	}
	pos.x += g->player.width / 2;
	pos.y += g->player.height / 2;
	end_pos.x = pos.x + cos(g->player.angle) * 100;
    end_pos.y = pos.y + sin(g->player.angle) * 100;
    draw_line(g, pos, end_pos);
}

bool	has_wall_at(t_game *g, float x, float y)
{
	if (x < 0 || x > g->map.width * TILE_SIZE || y < 0 || y > g->map.height * TILE_SIZE)
		return (true);
	return (g->map.arr[(int)(y / TILE_SIZE)][(int)(x / TILE_SIZE)] == 1);
}

void	check_wall_collision(t_game *g, float dx, float dy)
{
	// if (!has_wall_at(g, g->player.pos.x + dx + g->player.turn_direction * (g->player.width / 2), g->player.pos.y))
	// 	g->player.pos.x += dx;
	// if (!has_wall_at(g, g->player.pos.x, g->player.pos.y + dy + g->player.walk_direction * (g->player.height / 2)))
	// 	g->player.pos.y += dy;
	if (!has_wall_at(g, g->player.pos.x + dx * PLAYER_SCALE, g->player.pos.y))
		g->player.pos.x += dx;
	if (!has_wall_at(g, g->player.pos.x, g->player.pos.y + dy * PLAYER_SCALE))
		g->player.pos.y += dy;
}

int	player_movement(t_game *g)
{
	float	sin_a;
	float	cos_a;
	float	dx, dy;
	float	speed, speed_sin, speed_cos;

	sin_a = sin(g->player.angle);
	cos_a = cos(g->player.angle);
	dx = 0;
	dy = 0;
	speed = g->player.speed * g->delta_time;
	speed_sin = speed * sin_a;
	speed_cos = speed * cos_a;
	if (g->player.walk_direction == 1)
	{
		dx += -speed_cos;
		dy += -speed_sin;
	}
	if (g->player.walk_direction == -1)
	{
		dx += speed_cos;
		dy += speed_sin;
	}
	if (g->player.turn_direction == 1)
	{
		dx += -speed_sin;
		dy += speed_cos;
	}
	if (g->player.turn_direction == -1)
	{
		dx += speed_sin;
		dy += -speed_cos;
	}
	check_wall_collision(g, dx, dy);
	if (g->player.rotation_direction == 1)
		g->player.angle += g->player.rot_speed * g->delta_time;
	if (g->player.rotation_direction == -1)
		g->player.angle -= g->player.rot_speed * g->delta_time;
	g->player.angle = fmod(g->player.angle, 2 * M_PI);
	return (RETURN_SUCCESS);
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int	get_t(int trgb)
{
	return ((trgb >> 24) & 0xFF);
}

int	get_r(int trgb)
{
	return ((trgb >> 16) & 0xFF);
}

int	get_g(int trgb)
{
	return ((trgb >> 8) & 0xFF);
}

int	get_b(int trgb)
{
	return (trgb & 0xFF);
}

void	draw_ray_rect(t_game *g, t_coords start, int width, int height, int color)
{
	t_iterators	it;
	// int	ceiling_color = create_trgb(0, g->assets.ceiling.r, g->assets.ceiling.g, g->assets.ceiling.b);
	// int	floor_color = create_trgb(0, g->assets.floor.r, g->assets.floor.g, g->assets.floor.b);

	// it.i = -1;
	// while (++it.i < start.y)
	// {
	// 	it.j = -1;
	// 	while (++it.j < width)
	// 		cub_pixel_put(g, it.j, it.i, ceiling_color);
	// }
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
		// if (start.x + width >= g->win.width)
		// 	width = g->win.width - start.x;
		// if (start.x + width < 0)
		// 	width = 0;
		// if (start.y + it.i + height >= g->win.height)
		// 	height = g->win.height - start.y - it.i;
		// if (start.y + it.i + height < 0)
		// 	height = 0;
		if (it.i == 0 || it.i == height - 1)
			used_color = 0x000000;
		it.j = -1;
		while (++it.j < width)
			if (start.y + it.i < g->win.height && start.x + it.j < g->win.width)
				cub_pixel_put(g, start.x + it.j, start.y + it.i, used_color);
	}
	// it.i = -1;
	// while (++it.i < g->win.height - start.y - height)
	// {
	// 	it.j = -1;
	// 	while (++it.j < width)
	// 		cub_pixel_put(g, it.j, start.y + height + it.i, floor_color);
	// }
}

// PYTHONIC WAY
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
	int			color;
	int			vert_wall_content;
	int			horz_wall_content;
	t_iterators	it;

	origin = g->player.pos;
	map_pos.x = (int)(origin.x / TILE_SIZE);
	map_pos.y = (int)(origin.y / TILE_SIZE);
	ray_angle = g->player.angle - HALF_FOV + 0.0001;
	float screen_dist = HALF_WIN_WIDTH / tan(HALF_FOV);
	it.i = -1;
	while (++it.i < NUM_RAYS)
	{
		g->rays[it.i].angle = ray_angle;
		g->rays[it.i].rayface_down = g->player.angle > 0 && g->player.angle < M_PI;
		g->rays[it.i].rayface_up = !g->rays[it.i].rayface_down;
		g->rays[it.i].rayface_right = g->player.angle < M_PI_2 || g->player.angle > 3 * M_PI / 2;
		g->rays[it.i].rayface_left = !g->rays[it.i].rayface_right;

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
			if (g->map.arr[abs((int)(horz_tile.y))][abs((int)(horz_tile.x))] == 1)
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
			if (g->map.arr[abs((int)(vert_tile.y))][abs((int)(vert_tile.x))] == 1)
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

		// fishbowl effect
		depth *= (float) cos(g->player.angle - ray_angle);

		float proj_height = (TILE_SIZE / depth) * screen_dist;

		t_coords	start;
		t_coords	end;
		start = g->player.pos;
		end.x = start.x + depth * cos_a;
		end.y = start.y + depth * sin_a;
		
		if (MINIMAP)
			draw_line(g, start, end);
		else
		{
			start.x = it.i * SCALE;
			start.y = HALF_WIN_HEIGHT - proj_height / 2;
			color = (depth_vert < depth_horz) ? 0x00FF00 : 0xFF0000;
			draw_ray_rect(g, start, SCALE, proj_height, color);
		}
		
		ray_angle += DELTA_ANGLE;
	}
}

// void	raycast(t_game *g)
// {
// 	t_coords	origin;
// 	t_coords	ray_dir;
// 	float		ray_angle;
// 	int			i;

// 	origin = g->player.pos;
// 	ray_angle = g->player.angle - HALF_FOV;
// 	i = -1;
// 	while (++i < NUM_RAYS)
// 	{
// 		ray_dir.x = cos(ray_angle);
// 		ray_dir.y = sin(ray_angle);
// 		// draw_line(g, origin, ray_dir);
// 		ray_angle += DELTA_ANGLE;		
// 	}
// }

void	draw_background(t_game *g)
{
	t_coords	start;
	t_coords	end;
	t_iterators	it;

	start.x = 0;
	start.y = 0;
	end.x = WIN_WIDTH;
	end.y = HALF_WIN_HEIGHT;
	int	ceiling_color = create_trgb(0, g->assets.ceiling.r, g->assets.ceiling.g, g->assets.ceiling.b);
	int	floor_color = create_trgb(0, g->assets.floor.r, g->assets.floor.g, g->assets.floor.b);
	it.i = -1;
	while (++it.i < WIN_WIDTH)
	{
		it.j = -1;
		while (++it.j < HALF_WIN_HEIGHT)
			cub_pixel_put(g, it.i, it.j, ceiling_color);
	}
	start.y = HALF_WIN_HEIGHT;
	end.y = WIN_HEIGHT;
	it.i = -1;
	while (++it.i < WIN_WIDTH)
	{
		it.j = HALF_WIN_HEIGHT - 1;
		while (++it.j < WIN_HEIGHT)
			cub_pixel_put(g, it.i, it.j, floor_color);
	}
}

void	draw_minimap(t_game *g)
{
	t_iterators	it;
	t_iterators	it2;
	int			tile_size;

	tile_size = 10;
	it.i = -1;
	while (++it.i < g->map.height)
	{
		it.j = -1;
		while (++it.j < g->map.width)
		{
			if (g->map.arr[it.i][it.j] == 1)
			{
				it2.i = -1;
				while (++it2.i < tile_size)
				{
					it2.j = -1;
					while (++it2.j < tile_size)
						if (it.i * tile_size + it2.i < g->win.height
							&& it.j * tile_size + it2.j < g->win.width
							&& (it2.i == 0 || it2.j == 0
							|| it2.i == tile_size - 1 || it2.j == tile_size - 1))
							cub_pixel_put(g, it.j * tile_size + it2.j, it.i * tile_size + it2.i, 0xFFFFFF);
						else
							cub_pixel_put(g, it.j * tile_size + it2.j, it.i * tile_size + it2.i, 0x000000);
				}
			}
		}
	}
	
	t_coords	player_pos;
	
	player_pos.x = g->player.pos.x / TILE_SIZE * tile_size;
	player_pos.y = g->player.pos.y / TILE_SIZE * tile_size;
	it.i = -1;
	while (++it.i < PLAYER_MINIMAP_HEIGHT)
	{
		it.j = -1;
		while (++it.j < PLAYER_MINIMAP_WIDTH)
			cub_pixel_put(g, player_pos.x + it.j - PLAYER_MINIMAP_WIDTH / 2, player_pos.y + it.i - PLAYER_MINIMAP_HEIGHT / 2, 0xFF0000);
	}
}

void	update(t_game *g)
{
	static float	ticks_last_frame = 0.0;

	if (ticks_last_frame < 0.5)
		ticks_last_frame = (float) current_time_ms();
	while ((float) current_time_ms() - (ticks_last_frame + FRAME_RATE) < 0)
		;
	g->delta_time = (float) (current_time_ms() - ticks_last_frame) / 1000.0f;
	ticks_last_frame = (float) current_time_ms();
}

int	cub_render(t_game *g)
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
		printf("FPS: %u\n", frames);
		last_fps = frames;
		frames = 0;
		g->start_time = clock();
	}
	update(g);
	if (MINIMAP)
		display_map(g);
	else
		draw_background(g);
	player_movement(g);
	raycast(g);
	if (MINIMAP)
		draw_player(g);
	else
		draw_minimap(g);
	mlx_put_image_to_window(g->mlx, g->win.ref, g->frame.ref, 0, 0);
	mlx_destroy_image(g->mlx, g->frame.ref);
	tmp = ft_itoa(last_fps);
	fps_str = ft_strjoin("FPS: ", tmp);
	free(tmp);
	mlx_string_put(g->mlx, g->win.ref, 10, 5, 0xFF0000, fps_str);
	free(fps_str);
	return (RETURN_SUCCESS);
}
