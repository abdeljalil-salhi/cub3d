/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 21:40:50 by absalhi           #+#    #+#             */
/*   Updated: 2023/05/19 12:16:15 by absalhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_constants(t_game *g)
{
	g->constants.frame_rate = 1000 / FPS;
	g->constants.half_win_width = WIN_WIDTH / 2;
	g->constants.half_win_height = WIN_HEIGHT / 2;
	g->constants.fov = 60 * (M_PI / 180);
	g->constants.half_fov = g->constants.fov / 2;
	g->constants.screen_dist = WIN_WIDTH / 2 / tan(g->constants.half_fov);
	g->constants.num_rays = WIN_WIDTH;
	g->constants.half_num_rays = g->constants.num_rays / 2;
	g->constants.scale = WIN_WIDTH / g->constants.num_rays;
	g->constants.delta_angle = g->constants.fov / g->constants.num_rays;
	g->constants.player_rotation_speed = 90 * (M_PI / 180);
	g->constants.tau = 2 * M_PI;
}

int	main(int argc, char **argv)
{
	t_game	g;

	ft_bzero(&g, sizeof(t_game));
	if (argc != 2)
		cub_errors_exit(&g, "\tUsage:\t./cub3D [filename].cub");
	init_constants(&g);
	if (cub_parser(&g, argv[1]))
		cub_errors_exit(&g, g.error.message);
	g.mlx = mlx_init();
	g.win.ref = mlx_new_window(g.mlx, g.win.width, g.win.height, NAME);
	if (cub_init(&g))
		cub_errors_exit(&g, g.error.message);
	g.allocated.soundtrack = true;
	srand((unsigned int) time(NULL));
	g.start_time = clock();
	mlx_hook(g.win.ref, ON_DESTROY, 0L, cub_free_memory, &g);
	mlx_hook(g.win.ref, ON_KEYDOWN, 0L, cub_key_hook, &g);
	mlx_hook(g.win.ref, ON_KEYUP, 0L, cub_key_release, &g);
	mlx_loop_hook(g.mlx, cub_render, &g);
	mlx_loop(g.mlx);
}
