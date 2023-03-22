/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 21:40:50 by absalhi           #+#    #+#             */
/*   Updated: 2023/03/22 10:24:16 by absalhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	cub_print_assets(t_game *g)
{
	printf("R : %d %d\n", g->win.width, g->win.height);
	printf("NO: %s\n", g->assets.north);
	printf("SO: %s\n", g->assets.south);
	printf("WE: %s\n", g->assets.west);
	printf("EA: %s\n", g->assets.east);
	printf("F : %3d %3d %3d\n", g->assets.floor.r, g->assets.floor.g, g->assets.floor.b);
	printf("C : %3d %3d %3d\n", g->assets.ceiling.r, g->assets.ceiling.g, g->assets.ceiling.b);
}

static void	cub_free_memory(t_game *g)
{
	cub_free(g->assets.north);
	cub_free(g->assets.south);
	cub_free(g->assets.west);
	cub_free(g->assets.east);
	if (g->allocated.map)
		cub_free_double_int(g->map.arr, g->win.height);
}

int	main(int argc, char **argv)
{
	t_game	g;

	ft_bzero(&g, sizeof(t_game));
	if (argc != 2)
		cub_errors_exit(&g, "\tUsage:\t./cub3D [filename].cub");
	if (cub_parser(&g, argv[1]))
		cub_errors_exit(&g, g.error.message);
	cub_print_assets(&g);
	cub_free_memory(&g);
	if (LEAKS)
		system("leaks cub3D");
	return (EXIT_SUCCESS);
}
