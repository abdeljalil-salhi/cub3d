/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 21:41:40 by absalhi           #+#    #+#             */
/*   Updated: 2023/05/20 01:02:35 by absalhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <fcntl.h>
# include <errno.h>
# include <math.h>
# include <time.h>
# include <mlx.h>
# include <signal.h>

# include "libft.h"
# include "structs.h"
# include "errors.h"

typedef unsigned long		t_ul;
typedef unsigned long long	t_ull;

# define NAME "cub3D"

# define FPS 40
# define TILE_SIZE 64
# define PLAYER_SPEED 250

# define WIN_WIDTH 1600
# define WIN_HEIGHT 900
# define NUM_RAYS WIN_WIDTH
# define MAX_DEPTH 100
# define PLAYER_WIDTH 10
# define PLAYER_HEIGHT 32
# define PLAYER_SCALE 3

# define RETURN_FAILURE 1
# define RETURN_SUCCESS 0
# define RETURN_DEFAULT 1

# define ERROR "\033[1;31m"
# define GREEN "\033[0;32m" 
# define YELLOW "\033[0;33m"
# define RESET "\033[0m"

enum
{
	TEXT_N = 0,
	TEXT_S,
	TEXT_E,
	TEXT_W,
};

enum
{
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_DESTROY = 17,
};

enum
{
	KEY_A = 0,
	KEY_D = 2,
	KEY_S = 1,
	KEY_W = 13,
	ESC = 53,
	ARROW_LEFT = 123,
	ARROW_RIGHT = 124,
};

enum
{
	PLAYER = 99,
};

/* --------------------------- UTILS --------------------------- */
/*
** cub_free.c
*/
int		cub_free_double_ptr(void **tab);
int		cub_free_double_int(int **tab, size_t size);
int		cub_free(void *ptr);
int		cub_free_memory(t_game *g);

/*
** cub_errors.c
*/
void	cub_errors_exit(t_game *g, char *err);
int		cub_errors_setter(t_game *g, char *err);
int		cub_errors_map(t_game *g, size_t size, char *err);

/*
** cub_keys.c
*/
int		cub_key_hook(int keycode, t_game *g);
int		cub_key_release(int keycode, t_game *g);

/*
** cub_pixel_put.c
*/
void	cub_pixel_put(t_game *g, float x, float y, int color);

/* --------------------------- PARSING --------------------------- */
/*
** cub_parser.c
*/
int		cub_parser(t_game *g, char *filename);
void	cub_init_game_struct(t_game *g, char *filename);

/*
** cub_file_parser.c
*/
int		cub_file_parser(t_game *g);
int		cub_parse_config(t_game *g);
int		cub_file_line_parse(t_game *g, char *line);
int		cub_parse_texture(t_game *g, char **line, char **t, bool *has_t);
/*
** cub_file_checker.c
*/
int		cub_check_disponibility(t_game *g);
int		cub_check_extension(t_game *g);

/*
** cub_file_line.c
*/
int		cub_file_line_parse_identifier(t_game *g, char **line);
int		cub_parse_TEXT(t_game *g, char **line, char **t, bool *has_t);
int		cub_parse_color(t_game *g, char **line, t_color *c, bool *has_c);

/*
** cub_map.c
*/
typedef struct s_cub_map_init
{
	int			lowest_indent;
	char		*quick_line;
	int			width;
	int			height;
	t_iterators	it;
}	t_cub_map_init;

int		cub_map_init(t_game *g);
int		cub_map_parse(t_game *g, char *line);
void	cub_map_init_norm(t_game *g, t_cub_map_init *s);

/*
** cub_check.c
*/
int		cub_check_map(t_game *g);
int		cub_check_occurences(t_game *g);
int		cub_map_check(t_game *g, char *line);

/* --------------------------- RENDERING --------------------------- */
int		cub_init(t_game *g);
int		cub_render(t_game *g);
int		player_movement(t_game *g);

/* --------------------------- LIBCUB --------------------------- */
int		cub_count_occurences(char *str, char c);
int		cub_count_int_occurences(int *arr, size_t size, int n);
bool	cub_line_empty(char *line);
int		cub_file_open(t_game *g, int *fd, char *filename);
t_ull	current_time_ms(void);
int		create_rgb(t_color color);

/* --------------------------- RAYCASTING --------------------------- */
void	check_horz_inters(t_game *g, int i, t_coords dist, float depth);
void	check_vert_inters(t_game *g, int i, t_coords dist, float depth);
bool	check_if_wall(int content);
void	final_inters(t_game *g, int i);
void	find_vert_steps(t_game *g, int i, t_coords *dist, float *depth);
void	find_hor_steps(t_game *g, int i, t_coords *dist, float *depth);

/* --------------------------- DRAWING --------------------------- */
void	draw_walls(t_game *g, t_iterators it, float ray_angle);

/* --------------------------- PLAYER_MOVEMENT --------------------------- */
int		player_movement(t_game *g);
bool	has_wall_at(t_game *g, float x, float y);
bool	check_if_wall(int content);

#endif
