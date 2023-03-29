/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_render.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 00:58:36 by absalhi           #+#    #+#             */
/*   Updated: 2023/03/29 01:08:32 by absalhi          ###   ########.fr       */
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
				cub_rect_put(g, it, 0xFFFFFF, 0);
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

int	player_movement(t_game *g)
{
	double	sin_a;
	double	cos_a;
	float	dx, dy;
	double	speed, speed_sin, speed_cos;

	sin_a = sin(g->player.angle);
	cos_a = cos(g->player.angle);
	dx = 0;
	dy = 0;
	speed = PLAYER_SPEED * g->delta_time;
	speed_sin = speed * sin_a;
	speed_cos = speed * cos_a;
	if (g->player.walk_direction == 1)
	{
		dx += speed_cos;
		dy += speed_sin;
	}
	if (g->player.walk_direction == -1)
	{
		dx += -speed_cos;
		dy += -speed_sin;
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
	g->player.pos.x += dx;
	g->player.pos.y += dy;
	if (g->player.rotation_direction == 1)
		g->player.angle += PLAYER_ROTATION_SPEED * g->delta_time;
	if (g->player.rotation_direction == -1)
		g->player.angle -= PLAYER_ROTATION_SPEED * g->delta_time;
	g->player.angle = fmod(g->player.angle, 2 * M_PI);
	return (RETURN_SUCCESS);
}

void	update(t_game *g)
{
	static double	ticks_last_frame = 0.0;

	if (ticks_last_frame < 0.5)
		ticks_last_frame = (double) current_time_ms();
	while ((double) current_time_ms() - (ticks_last_frame + FRAME_RATE) < 0)
		;
	g->delta_time = (double) (current_time_ms() - ticks_last_frame) / 1000.0f;
	ticks_last_frame = (double) current_time_ms();
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
	display_map(g);
	draw_player(g);
	player_movement(g);
	mlx_put_image_to_window(g->mlx, g->win.ref, g->frame.ref, 0, 0);
	mlx_destroy_image(g->mlx, g->frame.ref);
	tmp = ft_itoa(last_fps);
	fps_str = ft_strjoin("FPS: ", tmp);
	free(tmp);
	mlx_string_put(g->mlx, g->win.ref, 10, 5, 0xFF0000, fps_str);
	free(fps_str);
	return (RETURN_SUCCESS);
}
