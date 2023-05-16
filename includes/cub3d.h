/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 21:41:40 by absalhi           #+#    #+#             */
/*   Updated: 2023/05/16 09:17:50 by absalhi          ###   ########.fr       */
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

typedef unsigned long		t_ul;
typedef unsigned long long	t_ull;

# include "libft.h"
# include "structs.h"
# include "errors.h"

# define NAME "cub3D"

# define LEAKS 0

# ifndef DEBUG
#  define DEBUG 0
# endif

# ifndef NO_TEXTURES
#  define NO_TEXTURES 0
# endif

# ifndef MANDATORY
#  define MANDATORY 0
# endif

# ifdef MINIMAP
#  define FPS 80
#  define TILE_SIZE 32
#  define PLAYER_SPEED 200
# else
#  define MINIMAP 0
#  define FPS 40
#  define TILE_SIZE 64
#  define PLAYER_SPEED 250
# endif

# define FRAME_RATE (1000 / FPS)

# define WIN_WIDTH 1600
# define WIN_HEIGHT 900
# define HALF_WIN_WIDTH (WIN_WIDTH / 2)
# define HALF_WIN_HEIGHT (WIN_HEIGHT / 2)

# define FOV (60 * (M_PI / 180))
# define HALF_FOV (FOV / 2)
# define SCREEN_DIST HALF_WIN_WIDTH / tan(HALF_FOV)
# define NUM_RAYS WIN_WIDTH
# define HALF_NUM_RAYS NUM_RAYS / 2
# define SCALE (WIN_WIDTH / NUM_RAYS)
# define DELTA_ANGLE (FOV / NUM_RAYS)
# define MAX_DEPTH 100

# define PLAYER_WIDTH 10
# define PLAYER_HEIGHT 32
# define PLAYER_MINIMAP_WIDTH 5
# define PLAYER_MINIMAP_HEIGHT 3
# define PLAYER_SCALE 3
# define PLAYER_ROTATION_SPEED (90 * (M_PI / 180))

# define HEALTH_BAR_X 5
# define HEALTH_BAR_Y 1

# define MEDKIT_HEALING 25

# define CENTER_Y 105
# define RADIUS 100
# define CENTER_X (WIN_WIDTH - RADIUS - 5)
# define SCALE_FACTOR 3

# define RETURN_FAILURE 1
# define RETURN_SUCCESS 0
# define RETURN_DEFAULT 1

# define ERROR "\033[1;31m"
# define GREEN "\033[0;32m" 
# define YELLOW "\033[0;33m"
# define RESET "\033[0m"

# define TAU 2 * M_PI

enum
{
	TEXTURE_NORTH = 0,
	TEXTURE_SOUTH,
	TEXTURE_EAST,
	TEXTURE_WEST
};

enum
{
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_EXPOSE = 12,
	ON_DESTROY = 17
};

enum
{
	KEY_A = 0,
	KEY_D = 2,
	KEY_S = 1,
	KEY_W = 13,
	KEY_E = 14,
	KEY_P = 35,
	KEY_M = 46,
	KEY_SPACE = 49,
	ESC = 53,
	ARROW_LEFT = 123,
	ARROW_RIGHT = 124,
	ARROW_DOWN = 125,
	ARROW_UP = 126,
	KEY_COMMAND = 259,
};

enum
{
	RAY_FACING_UP = 1,
	RAY_FACING_DOWN,
	RAY_FACING_LEFT,
	RAY_FACING_RIGHT
};

enum
{
	DOOR_TOGGLING = 96,
	DOOR_OPENED,
	DOOR_CLOSED,
	PLAYER
};

enum
{
	WEAPON_SHOTGUN,
};

enum
{
	OBJECT_BARREL,
	OBJECT_PILLAR,
	OBJECT_LAMP,
	OBJECT_GREEN_LIGHT,
	OBJECT_MEDKIT,
	OBJECT_DOOR,
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
void	cub_rect_put(t_game *g, t_iterators pos, int color);
void	draw_rect(t_game *g, t_iterators pos, int width, int height, int color);

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

/*
** cub_file_checker.c
*/
int		cub_check_disponibility(t_game *g);
int		cub_check_extension(t_game *g);

/*
** cub_file_line.c
*/
int		cub_file_line_parse_identifier(t_game *g, char **line);
int		cub_parse_texture(t_game *g, char **line, char **t, bool *has_t);
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
bool	is_object(char c);

/*
** cub_check.c
*/
int		cub_check_map(t_game *g);
int		cub_check_occurences(t_game *g);
int		cub_map_check(t_game *g, char *line);

/* --------------------------- RENDERING --------------------------- */

int		cub_init(t_game *g);
int		cub_init_objects(t_game *g);
int		cub_init_textures(t_game *g);
int		cub_init_sprites(t_game *g);
int		cub_init_weapon(t_game *g);
int		cub_render_sprite(t_game *g);
int		cub_init_candlebra(t_game *g);
int		scale_img(t_game *g, t_iterators dimension);
int		cub_render(t_game *g);
int		player_movement(t_game *g);

/* --------------------------- LIBCUB --------------------------- */

int		cub_count_occurences(char *str, char c);
int		cub_count_int_occurences(int *arr, size_t size, int n);
bool	cub_line_empty(char *line);
int		cub_file_open(t_game *g, int *fd, char *filename);
t_ull	current_time_ms(void);

#endif
