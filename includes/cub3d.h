/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 21:41:40 by absalhi           #+#    #+#             */
/*   Updated: 2023/03/20 00:16:00 by absalhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <fcntl.h>
# include <mlx.h>

# include "libft.h"
# include "structs.h"
# include "errors.h"

# define RETURN_FAILURE 1
# define RETURN_SUCCESS 0
# define RETURN_DEFAULT 1

# define ERROR "\033[1;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define RESET "\033[0m"

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
	KEY_P = 35,
	KEY_SPACE = 49,
	ESC = 53,
	ARROW_LEFT = 123,
	ARROW_RIGHT = 124,
	ARROW_DOWN = 125,
	ARROW_UP = 126
};

/* --------------------------- UTILS --------------------------- */

/*
** cub_free.c
*/
int		cub_free_double_ptr(void **tab);
int		cub_free_double_int(int **tab, size_t size);
int		cub_free(void *ptr);

/*
** cub_errors.c
*/
void	cub_errors_exit(t_game *g, char *err);
int		cub_errors_setter(t_game *g, char *err);
int		cub_errors_map(t_game *g, size_t size, char *err);

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

/* --------------------------- LIBCUB --------------------------- */

int		cub_count_occurences(char *str, char c);

/* --------------------------- RENDERING --------------------------- */

#endif
