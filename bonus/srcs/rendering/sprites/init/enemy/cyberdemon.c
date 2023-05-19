/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cyberdemon.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 09:08:16 by absalhi           #+#    #+#             */
/*   Updated: 2023/05/19 11:01:01 by absalhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_cyberdemon_walk(t_game *g)
{
	g->textures.object_path[OBJECT_CYBERDEMON_WALK][0] = CYBERDEMON_WALK_0;
	g->textures.object_path[OBJECT_CYBERDEMON_WALK][1] = CYBERDEMON_WALK_1;
	g->textures.object_path[OBJECT_CYBERDEMON_WALK][2] = CYBERDEMON_WALK_2;
	g->textures.object_path[OBJECT_CYBERDEMON_WALK][3] = CYBERDEMON_WALK_3;
	g->textures.object_path[OBJECT_CYBERDEMON_WALK][4] = CYBERDEMON_WALK_4;
	g->textures.object_n_of_frames[OBJECT_CYBERDEMON_WALK] = 5;
	g->textures.object_frame_rate[OBJECT_CYBERDEMON_WALK] = 200;
	g->textures.object_scale[OBJECT_CYBERDEMON_WALK] = 1;
}

static void	init_cyberdemon_damaged(t_game *g)
{
	int	cyberdemon;

	cyberdemon = OBJECT_CYBERDEMON_DAMAGED;
	g->textures.object_path[cyberdemon][0] = CYBERDEMON_DAMAGED_0;
	g->textures.object_path[cyberdemon][1] = CYBERDEMON_DAMAGED_1;
	g->textures.object_n_of_frames[cyberdemon] = 2;
	g->textures.object_frame_rate[cyberdemon] = 200;
	g->textures.object_scale[cyberdemon] = 1;
}

static void	init_cyberdemon_attack(t_game *g)
{
	g->textures.object_path[OBJECT_CYBERDEMON_ATTACK][0] = CYBERDEMON_ATTACK_0;
	g->textures.object_path[OBJECT_CYBERDEMON_ATTACK][1] = CYBERDEMON_ATTACK_1;
	g->textures.object_n_of_frames[OBJECT_CYBERDEMON_ATTACK] = 2;
	g->textures.object_frame_rate[OBJECT_CYBERDEMON_ATTACK] = 200;
	g->textures.object_scale[OBJECT_CYBERDEMON_ATTACK] = 1;
}

static void	init_cyberdemon_death(t_game *g)
{
	g->textures.object_path[OBJECT_CYBERDEMON_DEATH][0] = CYBERDEMON_DEATH_0;
	g->textures.object_path[OBJECT_CYBERDEMON_DEATH][1] = CYBERDEMON_DEATH_1;
	g->textures.object_path[OBJECT_CYBERDEMON_DEATH][2] = CYBERDEMON_DEATH_2;
	g->textures.object_path[OBJECT_CYBERDEMON_DEATH][3] = CYBERDEMON_DEATH_3;
	g->textures.object_path[OBJECT_CYBERDEMON_DEATH][4] = CYBERDEMON_DEATH_4;
	g->textures.object_path[OBJECT_CYBERDEMON_DEATH][5] = CYBERDEMON_DEATH_5;
	g->textures.object_path[OBJECT_CYBERDEMON_DEATH][6] = CYBERDEMON_DEATH_6;
	g->textures.object_path[OBJECT_CYBERDEMON_DEATH][7] = CYBERDEMON_DEATH_7;
	g->textures.object_path[OBJECT_CYBERDEMON_DEATH][8] = CYBERDEMON_DEATH_8;
	g->textures.object_n_of_frames[OBJECT_CYBERDEMON_DEATH] = 9;
	g->textures.object_frame_rate[OBJECT_CYBERDEMON_DEATH] = 50;
	g->textures.object_scale[OBJECT_CYBERDEMON_DEATH] = 1;
}

void	init_cyberdemon(t_game *g)
{
	init_cyberdemon_walk(g);
	init_cyberdemon_damaged(g);
	init_cyberdemon_attack(g);
	init_cyberdemon_death(g);
}
