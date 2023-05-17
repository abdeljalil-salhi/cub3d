/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_render.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 00:58:36 by absalhi           #+#    #+#             */
/*   Updated: 2023/05/17 07:04:24 by absalhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define COLOR 0xFFFFFF

int	cub_render_sprite(t_game *g);

bool	check_if_wall(int content)
{
	return (content == 1 || content == 2 || content == 3
		|| content == 4 || content == 5);
}

void	display_map(t_game *g)
{
	t_iterators	it;

	it.i = -1;
	while (++it.i < g->map.height)
	{
		it.j = -1;
		while (++it.j < g->map.width)
			if (check_if_wall(g->map.arr[it.i][it.j]))
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
	return (check_if_wall(g->map.arr[(int)(y / TILE_SIZE)][(int)(x / TILE_SIZE)]));
}

bool	has_door_at(t_game *g, float x, float y)
{
	if (x < 0 || x > g->map.width * TILE_SIZE || y < 0 || y > g->map.height * TILE_SIZE)
		return (false);
	return (g->map.arr[(int)(y / TILE_SIZE)][(int)(x / TILE_SIZE)] == DOOR_CLOSED);
}

bool	has_door2_at(t_game *g, float x, float y)
{
	if (x < 0 || x > g->map.width * TILE_SIZE || y < 0 || y > g->map.height * TILE_SIZE)
		return (false);
	return (g->map.arr[(int)(y / TILE_SIZE)][(int)(x / TILE_SIZE)] == DOOR_CLOSED);
}

void	check_wall_collision(t_game *g, float dx, float dy)
{
	// if (!has_wall_at(g, g->player.pos.x + dx + g->player.turn_direction * (g->player.width / 2), g->player.pos.y))
	// 	g->player.pos.x += dx;
	// if (!has_wall_at(g, g->player.pos.x, g->player.pos.y + dy + g->player.walk_direction * (g->player.height / 2)))
	// 	g->player.pos.y += dy;
	if (!has_wall_at(g, g->player.pos.x + dx * PLAYER_SCALE, g->player.pos.y)
		&& !has_door2_at(g, g->player.pos.x + dx * PLAYER_SCALE, g->player.pos.y))
		g->player.pos.x += dx;
	if (!has_wall_at(g, g->player.pos.x, g->player.pos.y + dy * PLAYER_SCALE)
		&& !has_door2_at(g, g->player.pos.x, g->player.pos.y + dy * PLAYER_SCALE))
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
	if (g->player.rotation_direction == 1 && !g->paused)
		// g->player.angle += g->player.rot_speed * g->delta_time;
		g->player.angle += g->mouse.angle * g->delta_time;
	if (g->player.rotation_direction == -1 && !g->paused)
		// g->player.angle -= g->player.rot_speed * g->delta_time;
		g->player.angle -= g->mouse.angle * g->delta_time;
	if (!g->paused)
		g->player.angle = fmod(g->player.angle, TAU);
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

t_image	get_texture(t_game *g, int ind)
{
	if (g->rays[ind].content_hit >= 1 && g->rays[ind].content_hit <= 5)
		return (g->textures.walls[g->rays[ind].content_hit - 1]);
	return (g->textures.walls[0]);
}

bool	is_enemy(int type)
{
	return (type >= OBJECT_SOLDIER_WALK && type <= OBJECT_SOLDIER_DEATH);
}

void	check_if_enemy(t_game *g, int x, int y)
{
	int	i;

	i = -1;
	while (++i < g->objects_count)
	{
		if (is_enemy(g->objects[i].type))
		{
			if ((int)(g->objects[i].pos.x / TILE_SIZE) == x && (int)(g->objects[i].pos.y / TILE_SIZE) == y
				&& g->player.shooting && g->player.damaging
				&& hypot(g->objects[i].pos.x - g->player.pos.x, g->objects[i].pos.y - g->player.pos.y) <= g->textures.weapon.range[g->textures.weapon.type])
			{
				g->player.damaging = false;
				g->objects[i].state = ENEMY_DAMAGED;
				g->objects[i].health -= g->textures.weapon.damage[g->textures.weapon.type];
				if (g->objects[i].health <= 0)
				{
					g->objects[i].health = 0;
					g->objects[i].state = ENEMY_DEATH;
					g->player.score += g->objects[i].bounty;
				}
			}
		}
	}
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
	// int			color;
	int			vert_wall_content;
	int			horz_wall_content;
	t_iterators	it;

	origin = g->player.pos;
	map_pos.x = (int)(origin.x / TILE_SIZE);
	map_pos.y = (int)(origin.y / TILE_SIZE);
	ray_angle = g->player.angle - HALF_FOV + 0.0001;
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

		// fishbowl effect
		depth *= (float) cos(g->player.angle - ray_angle);
		float proj_height = (TILE_SIZE / depth) * SCREEN_DIST;

		t_coords	start;
		t_coords	end;
		start = g->player.pos;
		end.x = start.x + depth * cos_a;
		end.y = start.y + depth * sin_a;
		
		if (MINIMAP)
			draw_line(g, start, end);
		else
		{
			int	wall_top_pixel;
			int	wall_bottom_pixel;
			int	text_offset_x;
			int	text_offset_y;
			int	i;
			unsigned int	textcolor;

			wall_top_pixel = HALF_WIN_HEIGHT - ((int) proj_height) / 2;
			wall_top_pixel = wall_top_pixel < 0 ? 0 : wall_top_pixel;
			wall_bottom_pixel = HALF_WIN_HEIGHT + ((int) proj_height) / 2;
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
			// ceiling
			i = -1;
			while (++i < wall_top_pixel)
			{
				if (NO_TEXTURES)
					cub_pixel_put(g, it.i * SCALE, i, 0xD6DBDF);
				else
				{
					straight_dist = SCREEN_DIST * PLAYER_HEIGHT  /  (i - HALF_WIN_HEIGHT);
					dist = straight_dist / cos_r;
					ceil.x = g->player.pos.x - cos_a * dist;
					ceil.y = g->player.pos.y - sin_a * dist;
					text_offset_x = (int) ceil.x % TILE_SIZE;
					text_offset_y = (int) ceil.y % TILE_SIZE;
					ceil_textcolor = ((unsigned int *) g->textures.ceil.addr)[text_offset_y * TILE_SIZE + text_offset_x] & COLOR;
					cub_pixel_put(g, it.i * SCALE, i, ceil_textcolor);
				}
			}
			// walls 
			if (g->rays[it.i].vertical_hit)
				text_offset_x = (int) vert_intersection.y;
			else
				text_offset_x = (int) horz_intersection.x;
			i = wall_top_pixel - 1;
			while (++i < wall_bottom_pixel)
			{
				text_offset_y = (i + (int) proj_height / 2 - HALF_WIN_HEIGHT) * (TILE_SIZE / proj_height);
				if (NO_TEXTURES)
					g->rays[it.i].vertical_hit
						? cub_pixel_put(g, it.i * SCALE, i, 0x00FF00)
						: cub_pixel_put(g, it.i * SCALE, i, 0xFF0000); 
				else if (MANDATORY)
				{
					if (g->rays[it.i].content_hit == DOOR_CLOSED)
						textcolor = ((unsigned int *) get_texture(g, it.i).addr)[(text_offset_y * TILE_SIZE) + text_offset_x];
					else if (g->rays[it.i].vertical_hit)
					{
						if (horz_intersection.x > g->player.pos.x)
							textcolor = ((unsigned int *) g->textures.sides[TEXTURE_EAST].addr)[(text_offset_y * TILE_SIZE) + text_offset_x];
						else
							textcolor = ((unsigned int *) g->textures.sides[TEXTURE_WEST].addr)[(text_offset_y * TILE_SIZE) + text_offset_x];
					}
					else
					{
						if (vert_intersection.y > g->player.pos.y)
							textcolor = ((unsigned int *) g->textures.sides[TEXTURE_SOUTH].addr)[(text_offset_y * TILE_SIZE) + text_offset_x];
						else
							textcolor = ((unsigned int *) g->textures.sides[TEXTURE_NORTH].addr)[(text_offset_y * TILE_SIZE) + text_offset_x];
					}
					cub_pixel_put(g, it.i * SCALE, i, textcolor);
				}
				else
				{
					textcolor = ((unsigned int *) get_texture(g, it.i).addr)[(text_offset_y * TILE_SIZE) + text_offset_x] & COLOR;
					cub_pixel_put(g, it.i * SCALE, i, textcolor);
				}
			}
			// floor
			i--;
			while (++i < WIN_HEIGHT)
			{
				if (NO_TEXTURES)
					cub_pixel_put(g, it.i * SCALE, i, 0xD6DBDF);
				else
				{
					straight_dist = SCREEN_DIST * PLAYER_HEIGHT  /  (i - HALF_WIN_HEIGHT);
					dist = straight_dist / cos_r;
					floor.x = g->player.pos.x + cos_a * dist;
					floor.y = g->player.pos.y + sin_a * dist;
					text_offset_x = (int) floor.x % TILE_SIZE;
					text_offset_y = (int) floor.y % TILE_SIZE;
					floor_textcolor = ((unsigned int *) g->textures.floor.addr)[text_offset_y * TILE_SIZE + text_offset_x] & COLOR;
					cub_pixel_put(g, it.i * SCALE, i, floor_textcolor);
				}
			}
		}
		ray_angle += DELTA_ANGLE;
		g->buffer[it.i] = depth;
	}
	cub_render_sprite(g);
}

void	draw_map(t_game *g)
{
	float	center_x;
	float	center_y;
	float	radius_x;
	float	radius_y;
	int		scale_factor;
	t_iterators	it;

	center_x = WIN_WIDTH / 2;
	center_y = WIN_HEIGHT / 2;
	radius_x = WIN_WIDTH * 0.3;
	radius_y = WIN_HEIGHT * 0.3;
	scale_factor = 2;
	it.i = -1;
	while (++it.i <= radius_y * 2)
	{
		it.j = -1;
		while (++it.j <= radius_x * 2)
		{
			if (it.i == 0 || it.j == 0 || it.i == radius_y * 2 || it.j == radius_x * 2)
				cub_pixel_put(g, center_x + it.j - radius_x, center_y + it.i - radius_y, 0xFFFFFF);
			else
			{
				float world_x = g->player.pos.x + scale_factor * (it.j - radius_x);
				float world_y = g->player.pos.y + scale_factor * (it.i - radius_y);
				if (world_x < 0 || world_x > g->map.width * TILE_SIZE || world_y < 0 || world_y > g->map.height * TILE_SIZE)
					cub_pixel_put(g, center_x + it.j - radius_x, center_y + it.i - radius_y, 0x000000);
				else if (g->map.arr[(int)(world_y / TILE_SIZE)][(int)(world_x / TILE_SIZE)] == DOOR_CLOSED)
					cub_pixel_put(g, center_x + it.j - radius_x, center_y + it.i - radius_y, 0x003300);
				else if (has_wall_at(g, world_x, world_y))
				{
					bool top = !has_wall_at(g, world_x, world_y - scale_factor) || has_door_at(g, world_x, world_y - scale_factor);
					bool bottom = !has_wall_at(g, world_x, world_y + scale_factor) || has_door_at(g, world_x, world_y + scale_factor);
					bool left = !has_wall_at(g, world_x - scale_factor, world_y) || has_door_at(g, world_x - scale_factor, world_y);
					bool right = !has_wall_at(g, world_x + scale_factor, world_y) || has_door_at(g, world_x + scale_factor, world_y);

					if (top || bottom || left || right)
						cub_pixel_put(g, center_x + it.j - radius_x, center_y + it.i - radius_y, 0xFFFFFF);
					else
						cub_pixel_put(g, center_x + it.j - radius_x, center_y + it.i - radius_y, 0x000000);
				}
			}
		}
	}

	it.i = -1;
	while (++it.i < PLAYER_MINIMAP_HEIGHT * 2)
	{
		it.j = -1;
		while (++it.j < PLAYER_MINIMAP_WIDTH * 2)
			cub_pixel_put(g, center_x + it.j - PLAYER_MINIMAP_WIDTH, center_y + it.i - PLAYER_MINIMAP_HEIGHT, 0xFF0000);
	}
}

void	draw_minimap(t_game *g)
{
	t_iterators	it;

	it.i = -1;
	while (++it.i <= RADIUS * 2)
	{
		it.j = -1;
		while (++it.j <= RADIUS * 2)
		{
			if (it.i == 0 || it.j == 0 || it.i == RADIUS * 2 || it.j == RADIUS * 2)
				cub_pixel_put(g, CENTER_X + it.j - RADIUS, CENTER_Y + it.i - RADIUS, 0xFFFFFF);
			else
			{
				float world_x = g->player.pos.x + SCALE_FACTOR * (it.j - RADIUS);
				float world_y = g->player.pos.y + SCALE_FACTOR * (it.i - RADIUS);
				if (world_x < 0 || world_x > g->map.width * TILE_SIZE || world_y < 0 || world_y > g->map.height * TILE_SIZE)
					cub_pixel_put(g, CENTER_X + it.j - RADIUS, CENTER_Y + it.i - RADIUS, 0x000000);
				else if (g->map.arr[(int)(world_y / TILE_SIZE)][(int)(world_x / TILE_SIZE)] == DOOR_CLOSED)
					cub_pixel_put(g, CENTER_X + it.j - RADIUS, CENTER_Y + it.i - RADIUS, 0x003300);
				else if (has_wall_at(g, world_x, world_y))
				{
					bool top = !has_wall_at(g, world_x, world_y - SCALE_FACTOR) || has_door_at(g, world_x, world_y - SCALE_FACTOR);
					bool bottom = !has_wall_at(g, world_x, world_y + SCALE_FACTOR) || has_door_at(g, world_x, world_y + SCALE_FACTOR);
					bool left = !has_wall_at(g, world_x - SCALE_FACTOR, world_y) || has_door_at(g, world_x - SCALE_FACTOR, world_y);
					bool right = !has_wall_at(g, world_x + SCALE_FACTOR, world_y) || has_door_at(g, world_x + SCALE_FACTOR, world_y);

					if (top || bottom || left || right)
						cub_pixel_put(g, CENTER_X + it.j - RADIUS, CENTER_Y + it.i - RADIUS, 0xFFFFFF);
					else
						cub_pixel_put(g, CENTER_X + it.j - RADIUS, CENTER_Y + it.i - RADIUS, 0x000000);
				}
			}
		}
	}

	it.i = -1;
	while (++it.i < PLAYER_MINIMAP_HEIGHT)
	{
		it.j = -1;
		while (++it.j < PLAYER_MINIMAP_WIDTH)
			cub_pixel_put(g, CENTER_X + it.j - PLAYER_MINIMAP_WIDTH / 2, CENTER_Y + it.i - PLAYER_MINIMAP_HEIGHT / 2, 0xFF0000);
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

void	draw_weapon(t_game *g)
{
	
	int	type;
	int	frame;

	type = g->textures.weapon.type;
	if (g->player.shooting)
	{
		if (g->textures.weapon.frame == 0 && !g->textures.weapon.animating)
		{
			g->player.damaging = true;
			g->textures.weapon.animating = true;
			g->textures.weapon.last_time = current_time_ms();
		}
		if (current_time_ms() - g->textures.weapon.last_time > g->textures.weapon.frame_rate[type])
		{
			g->textures.weapon.frame++;
			g->textures.weapon.last_time = current_time_ms();
		}
		if (g->textures.weapon.frame == g->textures.weapon.n_of_frames[type])
		{
			g->textures.weapon.animating = false;
			g->player.shooting = false;
			g->player.damaging = false;
			g->textures.weapon.frame = 0;
		}
	}
	frame = g->textures.weapon.frame;
	mlx_put_image_to_window(g->mlx, g->win.ref,
		g->textures.weapon.image[type][frame].ref,
		g->textures.weapon.pos.x, g->textures.weapon.pos.y);
}

void	put_tips(t_game *g)
{
	if (g->tips.open_door)
		mlx_string_put(g->mlx, g->win.ref, WIN_WIDTH / 2 - ft_strlen(DOOR_TIP) * 3,
			WIN_HEIGHT - 15, 0xFFFFFF, DOOR_TIP);
}

void	put_health(t_game *g)
{
	if (g->player.health > 100)
		g->player.health = 100;
	if (g->player.health < 0)
		g->player.health = 0;
	if (g->player.health == 0)
		mlx_put_image_to_window(g->mlx, g->win.ref, g->textures.health_bar[5].ref, 5, 1);
	else if (g->player.health <= 20)
		mlx_put_image_to_window(g->mlx, g->win.ref, g->textures.health_bar[4].ref, 5, 1);
	else if (g->player.health <= 40)
		mlx_put_image_to_window(g->mlx, g->win.ref, g->textures.health_bar[3].ref, 5, 1);
	else if (g->player.health <= 60)
		mlx_put_image_to_window(g->mlx, g->win.ref, g->textures.health_bar[2].ref, 5, 1);
	else if (g->player.health <= 99)
		mlx_put_image_to_window(g->mlx, g->win.ref, g->textures.health_bar[1].ref, 5, 1);
	else if (g->player.health <= 100)
		mlx_put_image_to_window(g->mlx, g->win.ref, g->textures.health_bar[0].ref, 5, 1);
}

void	display_enemy_splash(t_game *g);
void	display_medkit_splash(t_game *g);
void	put_upper_layer(t_game *g)
{
	if (g->player.taking_damage)
	{
		display_enemy_splash(g);
		mlx_put_image_to_window(g->mlx, g->win.ref, g->textures.splash[RED_SPLASH].ref, 0, 0);
	}
	else if (g->player.taking_medkit)
	{
		display_medkit_splash(g);
		mlx_put_image_to_window(g->mlx, g->win.ref, g->textures.splash[GREEN_SPLASH].ref, 0, 0);
	}
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
	if (MINIMAP)
		display_map(g);
	player_movement(g);
	raycast(g);
	if (MINIMAP)
		draw_player(g);
	else
		g->display_map ? draw_map(g) : draw_minimap(g);
	mlx_put_image_to_window(g->mlx, g->win.ref, g->frame.ref, 0, 0);
	if (!MINIMAP && !g->display_map)
		draw_weapon(g);
	put_tips(g);
	put_health(g);
	put_upper_layer(g);
	mlx_destroy_image(g->mlx, g->frame.ref);
	tmp = ft_itoa(last_fps);
	fps_str = ft_strjoin("FPS: ", tmp);
	free(tmp);
	mlx_string_put(g->mlx, g->win.ref, 15, 70, 0xBB0000, fps_str);
	free(fps_str);
	return (RETURN_SUCCESS);
}
