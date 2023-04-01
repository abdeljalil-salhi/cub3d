/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 22:05:12 by absalhi           #+#    #+#             */
/*   Updated: 2023/04/01 00:48:58 by absalhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include <stdbool.h>
# include <pthread.h>

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

typedef struct s_image
{
	void	*ref;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
}	t_image;

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

typedef struct s_coords
{
	float	x;
	float	y;
}	t_coords;

typedef struct s_alloc
{
	bool	map;
	bool	green_light;
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
	bool		rayface_down;
	bool		rayface_up;
	bool		rayface_right;
	bool		rayface_left;
	int			content_hit;
}	t_ray;

typedef struct s_player
{
	t_coords	pos;
	int			width;
	int			height;
	float		angle;
	float		speed;
	float		rot_speed;
	int			turn_direction;
	int			walk_direction;
	int			rotation_direction;
}	t_player;

typedef struct s_sprite
{
	t_image		image;
	char		**path;
	int			frame;
	int			n_of_frames;
}	t_sprite;

typedef struct s_texture
{
	t_image		redbrick;
	// t_image		pillar;
	//t_image		wood;
	t_image		eagle;
	//t_image		barrel;
	t_image		bluestone;
	t_sprite	green_light;
}	t_texture;

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
	t_texture	textures;
}	t_game;

/* --------------------------- UTILS --------------------------- */

typedef struct s_iterators
{
	int	i;
	int	j;
}	t_iterators;

#endif
