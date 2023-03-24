/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 22:05:12 by absalhi           #+#    #+#             */
/*   Updated: 2023/03/23 23:45:06 by absalhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include <stdbool.h>

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

typedef struct s_coords
{
	int	r;
	int	c;
}	t_coords;

typedef struct s_alloc
{
	bool	map;
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

typedef struct s_player
{
	unsigned int	degree;
}	t_player;

typedef struct s_game
{
	void		*mlx;
	t_window	win;
	t_map		map;
	t_error		error;
	t_parsing	parsing;
	t_assets	assets;
	t_player	player;
	bool		paused;
	bool		freeze;
	bool		game_over;
	t_alloc		allocated;
}	t_game;

/* --------------------------- UTILS --------------------------- */

typedef struct s_iterators
{
	int	i;
	int	j;
}	t_iterators;

#endif
