/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 02:47:09 by absalhi           #+#    #+#             */
/*   Updated: 2023/05/19 02:49:54 by absalhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	is_enemy(int type)
{
	return ((type >= OBJECT_SOLDIER_WALK && type <= OBJECT_SOLDIER_DEATH)
		|| (type >= OBJECT_CYBERDEMON_WALK && type <= OBJECT_CYBERDEMON_DEATH));
}

bool	is_enemy_walking(int type)
{
	return (type == OBJECT_SOLDIER_WALK
		|| type == OBJECT_CYBERDEMON_WALK);
}

bool	is_enemy_attacking(int type)
{
	return (type == OBJECT_SOLDIER_ATTACK
		|| type == OBJECT_CYBERDEMON_ATTACK);
}

bool	is_enemy_damaged(int type)
{
	return (type == OBJECT_SOLDIER_DAMAGED
		|| type == OBJECT_CYBERDEMON_DAMAGED);
}

bool	is_enemy_dead(int type)
{
	return (type == OBJECT_SOLDIER_DEATH
		|| type == OBJECT_CYBERDEMON_DEATH);
}
