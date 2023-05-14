/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 22:40:17 by absalhi           #+#    #+#             */
/*   Updated: 2023/05/14 18:27:51 by absalhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	cub_free_double_ptr(void **tab)
{
	int	i;

	i = -1;
	while (tab[++i])
		cub_free(tab[i]);
	cub_free(tab);
	return (RETURN_DEFAULT);
}

int	cub_free_double_int(int **tab, size_t size)
{
	int	i;

	i = -1;
	while ((size_t)++i < size)
		cub_free(tab[i]);
	cub_free(tab);
	return (RETURN_DEFAULT);
}

int	cub_free(void *ptr)
{
	free(ptr);
	return (RETURN_DEFAULT);
}

int	cub_free_memory(t_game *g)
{
	cub_free(g->assets.north);
	cub_free(g->assets.south);
	cub_free(g->assets.west);
	cub_free(g->assets.east);
	if (g->allocated.map)
		cub_free_double_int(g->map.arr, g->win.height);
	if (g->allocated.buffer)
		cub_free(g->buffer);
	if (LEAKS)
		system("leaks cub3D");
	mlx_mouse_show();
	exit(EXIT_SUCCESS);
}
