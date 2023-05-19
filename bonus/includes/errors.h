/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 23:58:34 by absalhi           #+#    #+#             */
/*   Updated: 2023/05/19 02:28:08 by absalhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

# define ERR_MALLOC "Malloc failed"
# define ERR_GNL "get_next_line failed"
# define ERR_FORK "Fork failed"

# define CONFIG_NOT_FOUND "UHH... Where is your config file ??"

# define FILE_NOT_FOUND "File not found"
# define FILE_PERMISSION_DENIED "You don't have permission to read a file"
# define FILE_UNKNOWN_ERROR "Error while opening a file"

# define EXTENSION_NO_OCCUR "Where is your file extension mate ?? o.O"
# define EXTENSION_MULTIPLE "WDYM multiple points in your filename ??"
# define EXTENSION_INVALID "Invalid file extension buddy... Please use .cub"

# define CONFIG_INVALID_LINE "Invalid line in your config file"

# define MAP_EMPTY_LINE "Empty line in your map"
# define MAP_INVALID_IDENTIFIER "Invalid identifier in your map"
# define MAP_DUPLICATE_IDENTIFIER "Duplicate identifier in your map"
# define MAP_TEXTURE_NOT_FOUND "A texture in your config file not found"
# define MAP_TEXTURE_PERMISSION "You don't have permissions to read a texture"
# define MAP_TEXTURE_UNKNOWN_ERROR "Error while reading a texture"
# define MAP_INVALID_COLOR "Invalid color in your config file"
# define MAP_INVALID_COLOR_RANGE "Invalid color range in your config [#0-255]"
# define MAP_INDEX_OUT_OF_RANGE "Indexed map out of range"
# define MAP_INVALID_CHAR "Invalid character in your map"
# define MAP_INVALID_BORDER "Invalid border in your map"
# define MAP_NO_PLAYERS "No players found in your map"
# define MAP_MULTIPLE_PLAYERS "Multiple players found in your map"

# define FAIL_WEAPON_LOAD "Failed to load weapon xpm"
# define FAIL_WEAPON_DATA "Failed to get data of weapon xpm"
# define FAIL_OBJECT_LOAD "Failed to load object xpm"
# define FAIL_OBJECT_DATA "Failed to get data of object xpm"
# define FAIL_HEALTHBAR_LOAD "Failed to load health bar xpm"
# define FAIL_HEALTHBAR_DATA "Failed to get data of health bar xpm"
# define FAIL_WALL_LOAD "Failed to load wall xpm"
# define FAIL_WALL_DATA "Failed to get data of wall xpm"
# define FAIL_DIGITS_LOAD "Failed to load digits xpm"
# define FAIL_DIGITS_DATA "Failed to get data of digits xpm"
# define FAIL_CEIL_LOAD "Failed to load ceil xpm"
# define FAIL_CEIL_DATA "Failed to get data of ceil xpm"
# define FAIL_FLOOR_LOAD "Failed to load floor xpm"
# define FAIL_FLOOR_DATA "Failed to get data of floor xpm"
# define FAIL_RED_SPLASH_LOAD "Failed to load red splash xpm"
# define FAIL_RED_SPLASH_DATA "Failed to get data of red splash xpm"
# define FAIL_GREEN_SPLASH_LOAD "Failed to load green splash xpm"
# define FAIL_GREEN_SPLASH_DATA "Failed to get data of green splash xpm"
# define FAIL_GAME_OVER_LOAD "Failed to load game over xpm"
# define FAIL_GAME_OVER_DATA "Failed to get data of game over xpm"

#endif
