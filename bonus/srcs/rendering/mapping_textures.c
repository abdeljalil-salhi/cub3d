#include "cub3d.h"

typedef struct s_wall_text_mapping
{
	float			proj_height;
	int				wall_top_pixel;
	int				wall_bottom_pixel;
	float			cos_r;
	float			straight_dist;
	float			dist;
	t_iterators		text_offset;
}	t_wall_text_mapping;

void	draw_ceil(t_game *g, t_iterators it, t_wall_text_mapping *w_t_mapping)
{
	int				i;
	t_coords		ceil;
	unsigned int	ceil_textcolor;
	int				text_ind;

	i = -1;
	while (++i < w_t_mapping->wall_top_pixel)
	{
		w_t_mapping->straight_dist = g->constants.screen_dist * PLAYER_HEIGHT
			/ (i - g->constants.half_win_height);
		w_t_mapping->dist = w_t_mapping->straight_dist / w_t_mapping->cos_r;
		ceil.x = g->player.pos.x - g->rays[it.i].cos_a * w_t_mapping->dist;
		ceil.y = g->player.pos.y - g->rays[it.i].sin_a * w_t_mapping->dist;
		w_t_mapping->text_offset.j = (int) ceil.x % TILE_SIZE;
		w_t_mapping->text_offset.i = (int) ceil.y % TILE_SIZE;
		text_ind = w_t_mapping->text_offset.i * TILE_SIZE
			+ w_t_mapping->text_offset.j;
		ceil_textcolor = ((unsigned int *) g->textures.ceil.addr)[text_ind]
			& INJECTED_COLOR;
		pixel_put(g, it.i * g->constants.scale, i, ceil_textcolor);
	}
}

void	draw_floor(t_game *g, t_iterators it, t_wall_text_mapping *w_t_mapping)
{
	int				i;
	t_coords		floor;
	unsigned int	floor_textcolor;
	int				text_ind;

	i = w_t_mapping->wall_bottom_pixel - 1;
	while (++i < WIN_HEIGHT)
	{
		w_t_mapping->straight_dist = g->constants.screen_dist * PLAYER_HEIGHT
			/ (i - g->constants.half_win_height);
		w_t_mapping->dist = w_t_mapping->straight_dist / w_t_mapping->cos_r;
		floor.x = g->player.pos.x + g->rays[it.i].cos_a * w_t_mapping->dist;
		floor.y = g->player.pos.y + g->rays[it.i].sin_a * w_t_mapping->dist;
		w_t_mapping->text_offset.j = (int) floor.x % TILE_SIZE;
		w_t_mapping->text_offset.i = (int) floor.y % TILE_SIZE;
		text_ind = w_t_mapping->text_offset.i * TILE_SIZE
			+ w_t_mapping->text_offset.j;
		floor_textcolor = ((unsigned int *) g->textures.floor.addr)[text_ind]
			& INJECTED_COLOR;
		pixel_put(g, it.i * g->constants.scale, i, floor_textcolor);
	}
}

void	draw_walls(t_game *g, t_iterators it, t_wall_text_mapping *w_t_mapping)
{
	int				i;
	unsigned int	text_color;
	int				text_ind;

	if (g->rays[it.i].vertical_hit)
		w_t_mapping->text_offset.j = (int) g->rays[it.i].vert_inters.y;
	else
		w_t_mapping->text_offset.j = (int) g->rays[it.i].horz_inters.x;
	i = w_t_mapping->wall_top_pixel - 1;
	while (++i < w_t_mapping->wall_bottom_pixel)
	{
		w_t_mapping->text_offset.i = (i + (int) w_t_mapping->proj_height / 2
				- g->constants.half_win_height)
			* (TILE_SIZE / w_t_mapping->proj_height);
		text_ind = w_t_mapping->text_offset.i * TILE_SIZE
			+ w_t_mapping->text_offset.j;
		text_color = ((unsigned int *) get_texture(g, it.i).addr)[text_ind]
			& INJECTED_COLOR;
		pixel_put(g, it.i * g->constants.scale, i, text_color);
	}
}

void	draw_world(t_game *g, t_iterators it, float ray_angle)
{
	float				depth;
	t_wall_text_mapping	w_t_mapping;

	depth = (float) cos(g->player.angle - ray_angle) * g->rays[it.i].depth;
	w_t_mapping.proj_height = (TILE_SIZE / depth) * g->constants.screen_dist;
	w_t_mapping.wall_top_pixel = g->constants.half_win_height
		- ((int) w_t_mapping.proj_height) / 2;
	if (w_t_mapping.wall_top_pixel < 0)
		w_t_mapping.wall_top_pixel = 0;
	w_t_mapping.wall_bottom_pixel = g->constants.half_win_height
		+ ((int) w_t_mapping.proj_height) / 2;
	if (w_t_mapping.wall_bottom_pixel > WIN_HEIGHT)
		w_t_mapping.wall_bottom_pixel = WIN_HEIGHT;
	w_t_mapping.cos_r = cos(g->player.angle - ray_angle);
	draw_ceil(g, it, &w_t_mapping);
	draw_walls(g, it, &w_t_mapping);
	draw_floor(g, it, &w_t_mapping);
	g->buffer[it.i] = depth;
}
