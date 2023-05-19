/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 21:41:40 by absalhi           #+#    #+#             */
/*   Updated: 2023/05/19 11:28:44 by absalhi          ###   ########.fr       */
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

typedef unsigned long		t_ul;
typedef unsigned long long	t_ull;

# include "libft.h"
# include "structs.h"
# include "errors.h"
# include "paths.h"

# define NAME "cub3D"
# define TMP "assets/sounds/.tmp"

# ifndef NO_TEXTURES
#  define NO_TEXTURES 0
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
	TEXTURE_WEST,
};

enum
{
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_EXPOSE = 12,
	ON_DESTROY = 17,
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
	KEY_1 = 18,
	KEY_2 = 19,
	KEY_3 = 20,
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
	RAY_FACING_RIGHT,
};

enum
{
	DOOR_TOGGLING = 95,
	DOOR_OPENED,
	DOOR_CLOSED,
	PLAYER,
	ENEMY_WALK,
	ENEMY_DAMAGED,
	ENEMY_ATTACK,
	ENEMY_DEATH,
};

enum
{
	WEAPON_KNIFE,
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
	OBJECT_SOLDIER_WALK,
	OBJECT_SOLDIER_DAMAGED,
	OBJECT_SOLDIER_ATTACK,
	OBJECT_SOLDIER_DEATH,
	OBJECT_CYBERDEMON_WALK,
	OBJECT_CYBERDEMON_DAMAGED,
	OBJECT_CYBERDEMON_ATTACK,
	OBJECT_CYBERDEMON_DEATH,
	OBJECT_WEAPON_SHOTGUN,
};

enum
{
	RED_SPLASH,
	GREEN_SPLASH,
};

enum
{
	ENEMY_HEALTH,
	ENEMY_BOUNTY,
	ENEMY_PRECISION,
	ENEMY_DAMAGE,
	ENEMY_RANGE,
	ENEMY_SPEED,
};

enum
{
	SOUND_THEME,
	SOUND_NPC_ATTACK,
	SOUND_NPC_DEATH,
	SOUND_NPC_DAMAGED,
	SOUND_PLAYER_DAMAGED,
	SOUND_SHOTGUN,
	SOUND_DOOR_CLOSE,
	SOUND_DOOR_OPEN,
	SOUND_SHOTGUN_SWITCH,
	SOUND_KNIFE,
	SOUND_KNIFE_SWITCH,
};

/* --------------------------- UTILS --------------------------- */

/*
** errors.c
*/
void	errors_exit(t_game *g, char *err);
int		errors_setter(t_game *g, char *err);
int		errors_map(t_game *g, size_t size, char *err);

/*
** free_memory.c
*/
int		free_double_ptr(void **tab);
int		free_double_int(int **tab, size_t size);
int		free_ptr(void *ptr);
int		free_memory(t_game *g);

/*
** image_scaling.c
*/
int		scale_image(t_game *g, t_iterators dimension);

/*
** keyboard_hooks.c
*/
int		hook_key_press(int keycode, t_game *g);
int		hook_key_release(int keycode, t_game *g);

/*
** mouse_hooks.c
*/
int		hook_mouse_press(int code, int x, int y, t_game *g);
int		hook_mouse_release(int code, int x, int y, t_game *g);

/*
** pixel_put.c
*/
void	pixel_put(t_game *g, float x, float y, int color);
void	filled_rect_put(t_game *g, t_iterators pos, int color);
void	rect_put(t_game *g, t_iterators pos, t_iterators dimension, int color);

/*
** sounds.c
*/
int		init_sounds(t_game *g);
int		afplay(t_game *g, int sound);
void	play_sound_track(t_game *g);
void	play_sound_effect(t_game *g, int sound);
void	stop_sound_track(t_game *g);

/* --------------------------- PARSING --------------------------- */

typedef struct s_parsing_analyzer
{
	int			lowest_indent;
	char		*quick_line;
	int			width;
	int			height;
	t_iterators	it;
}	t_parsing_analyzer;

int		config_parser(t_game *g, char *filename);
int		file_parser(t_game *g);
int		check_disponibility(t_game *g);
int		check_extension(t_game *g);
int		parse_config(t_game *g);
int		map_init(t_game *g);
int		map_check(t_game *g, char *line);
int		map_parse(t_game *g, char *line);
void	map_analyzer(t_game *g, t_parsing_analyzer *s);
bool	is_object(char c);
void	object_setter(t_game *g, char c, int i, int j);
int		check_map_borders_and_components(t_game *g);
int		check_player_occurences(t_game *g);

/* -------------------------------- RENDERING ------------------------------- */

/*
** rendering/
*/
int		init_textures(t_game *g);
int		init_sprites(t_game *g);
int		init_game(t_game *g);
bool	check_if_wall(int content);
bool	has_wall_at(t_game *g, float x, float y);
bool	has_door_at(t_game *g, float x, float y);
void	check_wall_collision(t_game *g, float dx, float dy);

/* ------------------ RENDERING - SPRITES --------------------- */

/*
** rendering/sprites/
*/
int		init_weapon(t_game *g);
int		init_objects(t_game *g);
void	init_soldier(t_game *g);
void	init_cyberdemon(t_game *g);
void	check_for_doors(t_game *g, int z);
void	check_for_enemies(t_game *g, int z);
bool	check_for_medkits(t_game *g, int z);
bool	check_for_weapon_drops(t_game *g, int z);
void	switch_weapon(t_game *g, int type);
void	show_door_tip(t_game *g, int z);
void	show_game_over_tip(t_game *g);
void	sort_objects(t_game *g);
void	compute_distances(t_game *g);

/*
** rendering/sprites/enemy/
*/
bool	is_enemy(int type);
bool	is_enemy_walking(int type);
bool	is_enemy_damaged(int type);
bool	is_enemy_attacking(int type);
bool	is_enemy_dead(int type);
void    enemy_movement(t_game *g, int z);
void	display_enemy_splash(t_game *g);
void	frame_enemy_walk(t_game *g, int z);
void	frame_enemy_damaged(t_game *g, int z);
void	frame_enemy_attack(t_game *g, int z);
void	frame_enemy_death(t_game *g, int z);

/*
** rendering/textures/
*/

/*
** rendering/textures/init/
*/
int		init_healthbar(t_game *g);
int		init_digits(t_game *g);
int		init_walls(t_game *g);
int		init_ceil(t_game *g);
int		init_floor(t_game *g);
int		init_red_splash(t_game *g);
int		init_green_splash(t_game *g);
int		init_game_over(t_game *g);

int		cub_render(t_game *g);
int		player_movement(t_game *g);

/* --------------------------- LIBCUB --------------------------- */

int		count_occurences(char *str, char c);
int		count_int_occurences(int *arr, size_t size, int n);
bool	line_empty(char *line);
int		file_open(t_game *g, int *fd, char *filename);
t_ull	current_time_ms(void);

/* --------------------------- TEXT --------------------------- */

# define DOOR_TIP "Press [E] to open the door"
# define GAME_OVER "Press [ESC] to quit"

#endif
