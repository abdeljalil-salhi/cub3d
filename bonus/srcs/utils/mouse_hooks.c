/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hooks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 05:10:49 by absalhi           #+#    #+#             */
/*   Updated: 2023/05/18 05:33:40 by absalhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	hook_mouse_press(int code, int x, int y, t_game *g)
{
	(void) x, (void) y;
	if (code == 1)
		g->mouse.left = true;
	else if (code == 2)
		g->mouse.right = true;
	return (RETURN_SUCCESS);
}

int	hook_mouse_release(int code, int x, int y, t_game *g)
{
	(void) x, (void) y;
	if (code == 1 && !g->player.shooting && !g->display_map && !g->paused)
	{
		g->player.shooting = true;
		g->mouse.left = false;
	}
	else if (code == 2 && !g->player.shooting && !g->display_map && !g->paused)
		g->mouse.right = false;
	return (RETURN_SUCCESS);
}
