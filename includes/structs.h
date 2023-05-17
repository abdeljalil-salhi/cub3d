/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 22:05:12 by absalhi           #+#    #+#             */
/*   Updated: 2023/05/18 00:17:51 by absalhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include <stdbool.h>
# include <pthread.h>

# define N_OF_SOUNDS 11

# define N_OF_OBJECTS 15
# define OBJECTS_MAX_FRAME 9

# define N_OF_WEAPONS 2
# define WEAPONS_MAX_FRAME 6

# define WEAPON_KNIFE_FRAMES 4
# define WEAPON_SHOTGUN_FRAMES 6

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
	bool		rayface_down;
	bool		rayface_up;
	bool		rayface_right;
	bool		rayface_left;
	bool		door_opened;
	t_coords	door_pos;
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
	int			health;
	int			score;
	bool		opening_door;
	bool		shooting;
	bool		damaging;
	bool		taking_damage;
	bool		taking_medkit;
	bool		switching_weapon;
}	t_player;

typedef struct s_image
{
	void	*ref;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
}	t_image;

typedef struct s_weapon
{
	int			type;
    t_image		image[N_OF_WEAPONS][WEAPONS_MAX_FRAME];
	char		*path[N_OF_WEAPONS][WEAPONS_MAX_FRAME];
	t_iterators	dimension[N_OF_WEAPONS];
	int			frame;
	int			n_of_frames[N_OF_WEAPONS];
	t_ul		frame_rate[N_OF_WEAPONS];
	clock_t		last_time;
	int			animating;
	t_coords	pos;
	int			damage[N_OF_WEAPONS];
	float		range[N_OF_WEAPONS];
	int			sound[N_OF_WEAPONS];
	bool		collected[N_OF_WEAPONS];
}	t_weapon;

typedef struct s_texture
{
	t_image		sides[4];
	t_image		health_bar[6];
	t_image		walls[5];
	t_image		floor;
	t_image		ceil;
	t_image		splash[2];
	t_image		game_over;
	t_weapon	weapon;
	t_image		object_image[N_OF_OBJECTS][OBJECTS_MAX_FRAME];
	char		*object_path[N_OF_OBJECTS][OBJECTS_MAX_FRAME];
	t_iterators	object_dimension[N_OF_OBJECTS];
	int			object_n_of_frames[N_OF_OBJECTS];
	t_ul		object_frame_rate[N_OF_OBJECTS];
	clock_t		object_last_time[N_OF_OBJECTS];
	float		object_scale[N_OF_OBJECTS];
}	t_texture;

typedef struct s_tips
{
	bool		open_door;
	bool		game_over;
}	t_tips;

typedef struct s_mouse
{
	bool		left;
	bool		right;
	bool		enabled;
	int			x;
	float		angle;
}	t_mouse;

typedef struct s_object
{
	int			infos[6];
	int			type;
	int			state;
	t_coords	pos;
	int			frame;
	bool		animating;
	clock_t		last_time;
	float		dist;
	bool		display;
	bool		visible;
}	t_object;

typedef struct s_sound
{
	char	*path;
	char	*volume;
}	t_sound;

typedef struct s_pid
{
	pid_t	soundtrack;
	pid_t	soundeffect[10];
	pid_t	playing_soundeffect[10];
}	t_pid;

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
	t_tips		tips;
	t_texture	textures;
	t_object	*objects;
	int			objects_count;
	t_mouse		mouse;
	t_sound		sound[N_OF_SOUNDS];
	t_pid		pid;
	float		*buffer;
	bool		display_map;
}	t_game;

#endif
