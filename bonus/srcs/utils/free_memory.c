/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 22:40:17 by absalhi           #+#    #+#             */
/*   Updated: 2023/05/18 05:28:40 by absalhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	free_double_ptr(void **tab)
{
	int	i;

	i = -1;
	while (tab[++i])
		free_ptr(tab[i]);
	free_ptr(tab);
	return (RETURN_DEFAULT);
}

int	free_double_int(int **tab, size_t size)
{
	int	i;

	i = -1;
	while ((size_t)++i < size)
		free_ptr(tab[i]);
	free_ptr(tab);
	return (RETURN_DEFAULT);
}

int	free_ptr(void *ptr)
{
	free(ptr);
	return (RETURN_DEFAULT);
}

int	free_memory(t_game *g)
{
	if (g->allocated.map)
		free_double_int(g->map.arr, g->win.height);
	if (g->allocated.buffer)
		free_ptr(g->buffer);
	mlx_mouse_show();
	if (open(TMP, O_CREAT | O_WRONLY | O_TRUNC, 0644) < 0)
		exit(EXIT_FAILURE);
	stop_sound_track(g);
	unlink(TMP);
	exit(EXIT_SUCCESS);
}
