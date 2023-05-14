# include "cub3d.h"

int	scale_img(t_game *g, t_iterators dimension)
{
	(void) g;
	(void) dimension;
	// t_image		scaled_img;
	// t_coords	scale;
	// t_iterators	it;
	// int			indx;

	// scale.y = dimension.i / (float)g->textures.candlebra.dimension.i;
	// scale.x = dimension.j / (float)g->textures.candlebra.dimension.j;
	// scaled_img.ref = mlx_new_image(g->mlx, dimension.j, dimension.i);
	// if (!scaled_img.ref)
	// 	return (cub_errors_setter(g, "Failed to load candlebra xpm."));
	// scaled_img.addr = mlx_get_data_addr(scaled_img.ref, &scaled_img.bpp, &scaled_img.line_length, &scaled_img.endian);
	// if (!scaled_img.addr)
	// 	return (cub_errors_setter(g, "Failed to load candlebra xpm."));
	// it.i = -1;
	// while (++it.i < dimension.i)
	// {
	// 	it.j = -1;
	// 	while(++it.j < dimension.j)
	// 	{
	// 		indx = ((int)(it.i / scale.y) * g->textures.candlebra.dimension.j + (int)(it.j / scale.x));
	// 		((unsigned int *)scaled_img.addr)[it.i * dimension.j + it.j] = ((unsigned int *)g->textures.candlebra.image.addr)[indx];
	// 	}
	// }
	// g->textures.candlebra.dimension.i = dimension.i;
	// g->textures.candlebra.dimension.j = dimension.j;
	// mlx_destroy_image(g->mlx, g->textures.candlebra.image.ref);
	// g->textures.candlebra.image  = scaled_img;
	return (EXIT_SUCCESS);
}