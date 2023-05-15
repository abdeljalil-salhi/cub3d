/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 21:40:50 by absalhi           #+#    #+#             */
/*   Updated: 2023/05/14 23:04:51 by absalhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	cub_print_map(t_game *g)
{
	t_iterators	it;

	it.i = -1;
	while (++it.i < g->map.height)
	{
		it.j = -1;
		while (++it.j < g->map.width)
		{
			if (g->map.arr[it.i][it.j] == -1 || g->map.arr[it.i][it.j] == 0)
				printf(" ");
			else if (g->map.arr[it.i][it.j] == 2)
				printf("P");
			else
				printf("%d", g->map.arr[it.i][it.j]);
		}
		printf("\n");
	}
}

static void	cub_print_assets(t_game *g)
{
	printf("R   : %d %d\n", g->win.width, g->win.height);
	printf("NO  : %s\n", g->assets.north);
	printf("SO  : %s\n", g->assets.south);
	printf("WE  : %s\n", g->assets.west);
	printf("EA  : %s\n", g->assets.east);
	printf("F   : %3d %3d %3d\n",
		g->assets.floor.r, g->assets.floor.g, g->assets.floor.b);
	printf("C   : %3d %3d %3d\n",
		g->assets.ceiling.r, g->assets.ceiling.g, g->assets.ceiling.b);
	printf("MAP :\n");
	cub_print_map(g);
}

int	cub_mouse_release(int code, int x, int y, t_game *g)
{
	(void) x, (void) y;
	if (code == 1 && !g->player.shooting)
	{
		g->player.shooting = true;
		g->mouse.left = false;
	}
	else if (code == 2)
		g->mouse.right = false;
	return (RETURN_SUCCESS);
}

int	cub_mouse_hook(int code, int x, int y, t_game *g)
{
	(void) x, (void) y;
	if (code == 1)
		g->mouse.left = true;
	else if (code == 2)
		g->mouse.right = true;
	return (RETURN_SUCCESS);
}

int	main(int argc, char **argv)
{
	t_game	g;

	ft_bzero(&g, sizeof(t_game));
	if (argc != 2)
		cub_errors_exit(&g, "\tUsage:\t./cub3D [filename].cub");
	if (cub_parser(&g, argv[1]))
		cub_errors_exit(&g, g.error.message);
	if (DEBUG)
		cub_print_assets(&g);
	g.mlx = mlx_init();
	g.win.ref = mlx_new_window(g.mlx, g.win.width, g.win.height, NAME);
	if (cub_init(&g))
		cub_errors_exit(&g, g.error.message);
	g.start_time = clock();
	g.mouse.enabled = true;
	mlx_hook(g.win.ref, ON_DESTROY, 0L, cub_free_memory, &g);
	mlx_hook(g.win.ref, ON_KEYDOWN, 0L, cub_key_hook, &g);
	mlx_hook(g.win.ref, ON_KEYUP, 0L, cub_key_release, &g);
	mlx_hook(g.win.ref, ON_MOUSEDOWN, 0L, cub_mouse_hook, &g);
	mlx_hook(g.win.ref, ON_MOUSEUP, 0L, cub_mouse_release, &g);
	mlx_loop_hook(g.mlx, cub_render, &g);
	mlx_loop(g.mlx);
}
