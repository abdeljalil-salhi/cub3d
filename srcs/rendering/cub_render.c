/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_render.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 00:58:36 by absalhi           #+#    #+#             */
/*   Updated: 2023/03/28 02:25:15 by absalhi          ###   ########.fr       */
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
				cub_rect_put(g, it, 0xFFFFFF, TILE_SIZE);
	}
}

void	draw_player(t_game *g)
{
	t_iterators	it;
	t_iterators	pos;
	int			size;

	size = 10;
	pos.i = g->player.pos.y - size / 2;
	pos.j = g->player.pos.x - size / 2;
	it.i = -1;
	while (++it.i < size)
	{
		it.j = -1;
		while (++it.j < size)
		{
			if (pos.i + it.i < g->win.height && pos.j + it.j < g->win.width)
				cub_pixel_put(g, pos.j + it.j, pos.i + it.i, 0xFF0000);
		}
	}
}

int	player_movement(t_game *g, int direction)
{
	(void) g;
	(void) direction;
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
	g->player.pos.y -= 50 * g->delta_time;
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
	mlx_put_image_to_window(g->mlx, g->win.ref, g->frame.ref, 0, 0);
	mlx_destroy_image(g->mlx, g->frame.ref);
	tmp = ft_itoa(last_fps);
	fps_str = ft_strjoin("FPS: ", tmp);
	free(tmp);
	mlx_string_put(g->mlx, g->win.ref, 10, 5, 0xFF0000, fps_str);
	free(fps_str);
	return (RETURN_SUCCESS);
}
