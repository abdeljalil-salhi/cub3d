/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_errors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 22:36:14 by absalhi           #+#    #+#             */
/*   Updated: 2023/05/17 08:08:47 by absalhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	stop_sound_track(t_game *g);
void	cub_errors_exit(t_game *g, char *err)
{
	ft_putstr_fd(ERROR "Error\n" RESET, STDERR_FILENO);
	ft_putstr_fd(err, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	if (g->allocated.map)
		cub_free_double_int(g->map.arr, (size_t) g->win.height);
	if (g->allocated.buffer)
		cub_free(g->buffer);
	mlx_mouse_show();
	if (LEAKS)
		system("leaks cub3D");
	if (open(TMP, O_CREAT | O_WRONLY | O_TRUNC, 0644) < 0)
		exit(EXIT_FAILURE);
	stop_sound_track(g);
	unlink(TMP);
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
