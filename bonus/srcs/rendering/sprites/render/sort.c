/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 11:02:40 by absalhi           #+#    #+#             */
/*   Updated: 2023/05/19 11:16:06 by absalhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	deep_copy_object_to_object(t_object *tmp, t_object *object)
{
	tmp->dist = object->dist;
	tmp->animating = object->animating;
	tmp->frame = object->frame;
	tmp->pos = object->pos;
	tmp->type = object->type;
	tmp->last_time = object->last_time;
	tmp->display = object->display;
	tmp->infos[ENEMY_HEALTH] = object->infos[ENEMY_HEALTH];
	tmp->infos[ENEMY_BOUNTY] = object->infos[ENEMY_BOUNTY];
	tmp->infos[ENEMY_PRECISION] = object->infos[ENEMY_PRECISION];
	tmp->infos[ENEMY_DAMAGE] = object->infos[ENEMY_DAMAGE];
	tmp->infos[ENEMY_RANGE] = object->infos[ENEMY_RANGE];
	tmp->infos[ENEMY_SPEED] = object->infos[ENEMY_SPEED];
	tmp->state = object->state;
	tmp->visible = object->visible;
}

static void	swap_objects(t_object *object1, t_object *object2)
{
	t_object	tmp;

	deep_copy_object_to_object(&tmp, object1);
	deep_copy_object_to_object(object1, object2);
	deep_copy_object_to_object(object2, &tmp);
}

void	sort_objects(t_game *g)
{
	t_iterators	it;
	
	it.i = -1;
	while (++it.i < g->objects_count)
	{
		it.j = it.i;
		while (++it.j < g->objects_count)
			if (g->objects[it.j].dist > g->objects[it.i].dist)
				swap_objects(&g->objects[it.i], &g->objects[it.j]);
	}
}
