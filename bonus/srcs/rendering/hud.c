/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 01:19:32 by absalhi           #+#    #+#             */
/*   Updated: 2023/05/20 01:22:19 by absalhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_tips(t_game *g)
{
	if (g->tips.game_over)
		mlx_string_put(g->mlx, g->win.ref,
			WIN_WIDTH / 2 - ft_strlen(GAME_OVER) * 3,
			WIN_HEIGHT - 15, 0xFFFFFF, GAME_OVER);
	else if (g->tips.open_door && !g->game_over)
		mlx_string_put(g->mlx, g->win.ref,
			WIN_WIDTH / 2 - ft_strlen(DOOR_TIP) * 3,
			WIN_HEIGHT - 15, 0xFFFFFF, DOOR_TIP);
}

void	draw_score(t_game *g)
{
	int	i;
	int	len;
	int	score;

	len = ft_nblen(g->player.score);
	score = g->player.score;
	i = -1;
	while (++i < len)
	{
		mlx_put_image_to_window(g->mlx, g->win.ref,
			g->textures.digits[score % 10].ref, 280 - 20 - i * 20, 60);
		score /= 10;
	}
}

void	put_player_infos(t_game *g)
{
	if (g->player.health > 100)
		g->player.health = 100;
	if (g->player.health < 0)
		g->player.health = 0;
	if (g->player.health == 0)
		mlx_put_image_to_window(g->mlx, g->win.ref,
			g->textures.health_bar[5].ref, 5, 1);
	else if (g->player.health <= 20)
		mlx_put_image_to_window(g->mlx, g->win.ref,
			g->textures.health_bar[4].ref, 5, 1);
	else if (g->player.health <= 40)
		mlx_put_image_to_window(g->mlx, g->win.ref,
			g->textures.health_bar[3].ref, 5, 1);
	else if (g->player.health <= 60)
		mlx_put_image_to_window(g->mlx, g->win.ref,
			g->textures.health_bar[2].ref, 5, 1);
	else if (g->player.health <= 99)
		mlx_put_image_to_window(g->mlx, g->win.ref,
			g->textures.health_bar[1].ref, 5, 1);
	else if (g->player.health <= 100)
		mlx_put_image_to_window(g->mlx, g->win.ref,
			g->textures.health_bar[0].ref, 5, 1);
	draw_score(g);
}

void	put_upper_layer(t_game *g)
{
	if (g->game_over)
	{
		show_game_over_tip(g);
		mlx_put_image_to_window(g->mlx, g->win.ref,
			g->textures.game_over.ref, 0, 0);
	}
	else if (g->player.taking_damage)
	{
		display_enemy_splash(g);
		mlx_put_image_to_window(g->mlx, g->win.ref,
			g->textures.splash[RED_SPLASH].ref, 0, 0);
	}
	else if (g->player.taking_medkit)
	{
		display_medkit_splash(g);
		mlx_put_image_to_window(g->mlx, g->win.ref,
			g->textures.splash[GREEN_SPLASH].ref, 0, 0);
	}
}
