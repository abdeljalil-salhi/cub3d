/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   soldier.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 08:49:59 by absalhi           #+#    #+#             */
/*   Updated: 2023/05/18 09:05:54 by absalhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_soldier_walk(t_game *g)
{
	g->textures.object_path[OBJECT_SOLDIER_WALK][0] = SOLDIER_WALK_0;
	g->textures.object_path[OBJECT_SOLDIER_WALK][1] = SOLDIER_WALK_1;
	g->textures.object_path[OBJECT_SOLDIER_WALK][2] = SOLDIER_WALK_2;
	g->textures.object_path[OBJECT_SOLDIER_WALK][3] = SOLDIER_WALK_3;
	g->textures.object_n_of_frames[OBJECT_SOLDIER_WALK] = 4;
	g->textures.object_frame_rate[OBJECT_SOLDIER_WALK] = 200;
	g->textures.object_scale[OBJECT_SOLDIER_WALK] = 0.8;
}

static void	init_soldier_damaged(t_game *g)
{
	g->textures.object_path[OBJECT_SOLDIER_DAMAGED][0] = SOLDIER_DAMAGED_0;
	g->textures.object_n_of_frames[OBJECT_SOLDIER_DAMAGED] = 1;
	g->textures.object_frame_rate[OBJECT_SOLDIER_DAMAGED] = 0;
	g->textures.object_scale[OBJECT_SOLDIER_DAMAGED] = 0.8;
}

static void	init_soldier_attack(t_game *g)
{
	g->textures.object_path[OBJECT_SOLDIER_ATTACK][0] = SOLDIER_ATTACK_0;
	g->textures.object_path[OBJECT_SOLDIER_ATTACK][1] = SOLDIER_ATTACK_1;
	g->textures.object_n_of_frames[OBJECT_SOLDIER_ATTACK] = 2;
	g->textures.object_frame_rate[OBJECT_SOLDIER_ATTACK] = 200;
	g->textures.object_scale[OBJECT_SOLDIER_ATTACK] = 0.8;
}

static void	init_soldier_death(t_game *g)
{
	g->textures.object_path[OBJECT_SOLDIER_DEATH][0] = SOLDIER_DEATH_0;
	g->textures.object_path[OBJECT_SOLDIER_DEATH][1] = SOLDIER_DEATH_1;
	g->textures.object_path[OBJECT_SOLDIER_DEATH][2] = SOLDIER_DEATH_2;
	g->textures.object_path[OBJECT_SOLDIER_DEATH][3] = SOLDIER_DEATH_3;
	g->textures.object_path[OBJECT_SOLDIER_DEATH][4] = SOLDIER_DEATH_4;
	g->textures.object_path[OBJECT_SOLDIER_DEATH][5] = SOLDIER_DEATH_5;
	g->textures.object_path[OBJECT_SOLDIER_DEATH][6] = SOLDIER_DEATH_6;
	g->textures.object_path[OBJECT_SOLDIER_DEATH][7] = SOLDIER_DEATH_7;
	g->textures.object_path[OBJECT_SOLDIER_DEATH][8] = SOLDIER_DEATH_8;
	g->textures.object_n_of_frames[OBJECT_SOLDIER_DEATH] = 9;
	g->textures.object_frame_rate[OBJECT_SOLDIER_DEATH] = 50;
	g->textures.object_scale[OBJECT_SOLDIER_DEATH] = 0.8;
}

void	init_soldier(t_game *g)
{
	init_soldier_walk(g);
	init_soldier_damaged(g);
	init_soldier_attack(g);
	init_soldier_death(g);
}
