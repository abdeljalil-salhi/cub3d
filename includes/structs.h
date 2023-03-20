/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 22:05:12 by absalhi           #+#    #+#             */
/*   Updated: 2023/03/19 23:44:03 by absalhi          ###   ########.fr       */
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

typedef struct s_game
{
	void		*mlx;
	t_window	win;
	t_map		map;
	t_error		error;
	bool		paused;
	bool		freeze;
	bool		game_over;
	t_alloc		allocated;
}	t_game;

#endif
