#include "cub3d.h"

void	mouse_state_helper(t_game *g, int x, int y)
{
	int	step_x;

	if (!g->paused)
	{
		step_x = x - g->mouse.x;
		g->mouse.angle = atan2(abs(step_x), WIN_WIDTH) * 180 / M_PI;
		if (step_x < 0)
			g->player.rotation_direction = -1;
		else if (step_x >= 0)
			g->player.rotation_direction = 1;
		g->mouse.x = x;
	}
	if ((g->mouse.x > WIN_WIDTH || g->mouse.x < 0) || g->paused)
	{
		g->mouse.x = WIN_WIDTH / 2;
		mlx_mouse_move(g->win.ref, WIN_WIDTH / 2, y);
	}
	if ((y > WIN_HEIGHT || y < 0) || g->paused)
		mlx_mouse_move(g->win.ref, x, WIN_HEIGHT / 2);
}

void	mouse_state(t_game *g)
{
	int	x;
	int	y;

	if (g->mouse.enabled)
	{
		mlx_mouse_get_pos(g->win.ref, &x, &y);
		mlx_mouse_hide();
		if (x != g->mouse.x)
			mouse_state_helper(g, x, y);
		else
			g->player.rotation_direction = 0;
	}
	else
		mlx_mouse_show();
}
