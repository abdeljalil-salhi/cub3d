#include "cub3d.h"

void	put_fps(t_game *g, unsigned int last_fps)
{
	char				*fps_str;
	char				*tmp;

	tmp = ft_itoa(last_fps);
	fps_str = ft_strjoin("FPS: ", tmp);
	free(tmp);
	mlx_string_put(g->mlx, g->win.ref, 15, 70, 0xBB0000, fps_str);
	free(fps_str);
}
