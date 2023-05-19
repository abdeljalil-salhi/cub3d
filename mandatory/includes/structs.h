/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 22:05:12 by absalhi           #+#    #+#             */
/*   Updated: 2023/05/19 12:16:07 by absalhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include <stdbool.h>

/* --------------------------- UTILS --------------------------- */

typedef struct s_iterators
{
	int	i;
	int	j;
}	t_iterators;

typedef struct s_coords
{
	float	x;
	float	y;
}	t_coords;

/* ---------------------------- GAME ---------------------------- */

typedef struct s_window
{
	void	*ref;
	int		width;
	int		height;
}	t_window;

typedef struct s_file
{
	char	*path;
	int		fd;
}	t_file;

typedef struct s_map
{
	t_file	file;
	int		**arr;
	int		width;
	int		height;
}	t_map;

typedef struct s_error
{
	char	*message;
	int		code;
}	t_error;

typedef struct s_alloc
{
	bool	map;
	bool	green_light;
	bool	weapon;
	bool	candlebra;
	bool	buffer;
	bool	soundtrack;
}	t_alloc;

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

typedef struct s_parsing
{
	bool	is_map;
	bool	map_initialized;
	bool	has_north;
	bool	has_south;
	bool	has_west;
	bool	has_east;
	bool	has_floor;
	bool	has_ceiling;
	int		lines_before_map;
	int		lowest_indent;
}	t_parsing;

typedef struct s_assets
{
	char	*north;
	char	*south;
	char	*west;
	char	*east;
	t_color	floor;
	t_color	ceiling;
}	t_assets;

typedef struct s_ray
{
	t_coords	wall_hit;
	float		angle;
	float		depth;
	bool		vertical_hit;
	int			content_hit;
	float		sin_a;
	float		cos_a;
	t_coords	horz_inters;
	t_coords	vert_inters;
	float		depth_horz;
	float		depth_vert;
	float		horz_wall_content;
	float		vert_wall_content;
	float		proj_h;
}	t_ray;

typedef struct s_player
{
	t_coords	pos;
	t_coords	map_pos;
	int			width;
	int			height;
	float		angle;
	float		speed;
	float		rot_speed;
	int			turn_direction;
	int			walk_direction;
	int			rotation_direction;
}	t_player;

typedef struct s_image
{
	void	*ref;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
}	t_image;

typedef struct s_constants
{
	float	frame_rate;
	float	half_win_width;
	float	half_win_height;
	float	fov;
	float	half_fov;
	float	screen_dist;
	int		num_rays;
	float	half_num_rays;
	float	scale;
	float	delta_angle;
	float	player_rotation_speed;
	float	tau;
}	t_constants;

typedef struct s_game
{
	void		*mlx;
	t_window	win;
	t_map		map;
	t_error		error;
	t_parsing	parsing;
	t_assets	assets;
	t_ray		*rays;
	t_player	player;
	t_image		frame;
	clock_t		start_time;
	float		delta_time;
	bool		paused;
	bool		freeze;
	bool		game_over;
	t_alloc		allocated;
	t_image		textures[4];
	t_constants	constants;
}	t_game;

#endif
