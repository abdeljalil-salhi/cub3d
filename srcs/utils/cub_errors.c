/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_errors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 22:36:14 by absalhi           #+#    #+#             */
/*   Updated: 2023/04/01 00:56:38 by absalhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	cub_errors_exit(t_game *g, char *err)
{
	ft_putstr_fd(ERROR "Error\n" RESET, STDERR_FILENO);
	ft_putstr_fd(err, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	if (g->allocated.map)
		cub_free_double_int(g->map.arr, (size_t) g->win.height);
	cub_free_textures(g);
	if (LEAKS)
		system("leaks cub3D");
	exit(EXIT_FAILURE);
}

int	cub_errors_setter(t_game *g, char *err)
{
	g->error.message = err;
	g->error.code = 1;
	return (RETURN_DEFAULT);
}

int	cub_errors_map(t_game *g, size_t size, char *err)
{
	return (cub_free_double_int(g->map.arr, size)
		+ cub_errors_setter(g, err));
}
