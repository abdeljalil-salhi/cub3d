/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cacodemon.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 23:59:13 by absalhi           #+#    #+#             */
/*   Updated: 2023/05/21 00:04:31 by absalhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_cacodemon_walk(t_game *g)
{
	g->textures.object_path[OBJECT_CACODEMON_WALK][0] = CACODEMON_WALK_0;
	g->textures.object_path[OBJECT_CACODEMON_WALK][1] = CACODEMON_WALK_1;
	g->textures.object_path[OBJECT_CACODEMON_WALK][2] = CACODEMON_WALK_2;
	g->textures.object_n_of_frames[OBJECT_CACODEMON_WALK] = 3;
	g->textures.object_frame_rate[OBJECT_CACODEMON_WALK] = 200;
	g->textures.object_scale[OBJECT_CACODEMON_WALK] = 0.9;
}

static void	init_cacodemon_damaged(t_game *g)
{
	g->textures.object_path[OBJECT_CACODEMON_DAMAGED][0] = CACODEMON_DAMAGED_0;
	g->textures.object_path[OBJECT_CACODEMON_DAMAGED][1] = CACODEMON_DAMAGED_1;
	g->textures.object_n_of_frames[OBJECT_CACODEMON_DAMAGED] = 2;
	g->textures.object_frame_rate[OBJECT_CACODEMON_DAMAGED] = 200;
	g->textures.object_scale[OBJECT_CACODEMON_DAMAGED] = 0.9;
}

static void	init_cacodemon_attack(t_game *g)
{
	g->textures.object_path[OBJECT_CACODEMON_ATTACK][0] = CACODEMON_ATTACK_0;
	g->textures.object_path[OBJECT_CACODEMON_ATTACK][1] = CACODEMON_ATTACK_1;
	g->textures.object_path[OBJECT_CACODEMON_ATTACK][2] = CACODEMON_ATTACK_2;
	g->textures.object_path[OBJECT_CACODEMON_ATTACK][3] = CACODEMON_ATTACK_3;
	g->textures.object_path[OBJECT_CACODEMON_ATTACK][4] = CACODEMON_ATTACK_4;
	g->textures.object_n_of_frames[OBJECT_CACODEMON_ATTACK] = 5;
	g->textures.object_frame_rate[OBJECT_CACODEMON_ATTACK] = 100;
	g->textures.object_scale[OBJECT_CACODEMON_ATTACK] = 0.9;
}

static void	init_cacodemon_death(t_game *g)
{
	g->textures.object_path[OBJECT_CACODEMON_DEATH][0] = CACODEMON_DEATH_0;
	g->textures.object_path[OBJECT_CACODEMON_DEATH][1] = CACODEMON_DEATH_1;
	g->textures.object_path[OBJECT_CACODEMON_DEATH][2] = CACODEMON_DEATH_2;
	g->textures.object_path[OBJECT_CACODEMON_DEATH][3] = CACODEMON_DEATH_3;
	g->textures.object_path[OBJECT_CACODEMON_DEATH][4] = CACODEMON_DEATH_4;
	g->textures.object_path[OBJECT_CACODEMON_DEATH][5] = CACODEMON_DEATH_5;
	g->textures.object_path[OBJECT_CACODEMON_DEATH][6] = CACODEMON_DEATH_6;
	g->textures.object_path[OBJECT_CACODEMON_DEATH][7] = CACODEMON_DEATH_7;
	g->textures.object_path[OBJECT_CACODEMON_DEATH][8] = CACODEMON_DEATH_8;
	g->textures.object_n_of_frames[OBJECT_CACODEMON_DEATH] = 9;
	g->textures.object_frame_rate[OBJECT_CACODEMON_DEATH] = 50;
	g->textures.object_scale[OBJECT_CACODEMON_DEATH] = 0.9;
}

void	init_cacodemon(t_game *g)
{
	init_cacodemon_walk(g);
	init_cacodemon_damaged(g);
	init_cacodemon_attack(g);
	init_cacodemon_death(g);
}
