#include "cub3d.h"

int	cub_init_weapon(t_game *g)
{
	int	i;
	// t_iterators	scaled_dimen;

	g->textures.weapon.path[WEAPON_SHOTGUN][0] = "assets/sprites/weapon/0.xpm";
	g->textures.weapon.path[WEAPON_SHOTGUN][1] = "assets/sprites/weapon/1.xpm";
	g->textures.weapon.path[WEAPON_SHOTGUN][2] = "assets/sprites/weapon/2.xpm";
	g->textures.weapon.path[WEAPON_SHOTGUN][3] = "assets/sprites/weapon/3.xpm";
    g->textures.weapon.path[WEAPON_SHOTGUN][4] = "assets/sprites/weapon/4.xpm";
	g->textures.weapon.path[WEAPON_SHOTGUN][5] = "assets/sprites/weapon/5.xpm";
	g->textures.weapon.type = WEAPON_SHOTGUN;
	g->textures.weapon.frame = 0;
	g->textures.weapon.n_of_frames[WEAPON_SHOTGUN] = WEAPON_SHOTGUN_FRAMES;
	g->textures.weapon.frame_rate[WEAPON_SHOTGUN] = 80;
	g->textures.weapon.damage[WEAPON_SHOTGUN] = 30;
	g->textures.weapon.range[WEAPON_SHOTGUN] = 300.0f;
	i = -1;
	while (++i < WEAPON_SHOTGUN_FRAMES)
	{
		g->textures.weapon.image[WEAPON_SHOTGUN][i].ref = mlx_xpm_file_to_image(g->mlx,
				g->textures.weapon.path[WEAPON_SHOTGUN][i],
				&g->textures.weapon.dimension[WEAPON_SHOTGUN].j,
				&g->textures.weapon.dimension[WEAPON_SHOTGUN].i);
		if (!g->textures.weapon.image[WEAPON_SHOTGUN][i].ref)
			return (cub_errors_setter(g, "Failed to load weapon xpm."));
		g->textures.weapon.image[WEAPON_SHOTGUN][i].addr = mlx_get_data_addr(g->textures.weapon.image[WEAPON_SHOTGUN][i].ref,
				&g->textures.weapon.image[WEAPON_SHOTGUN][i].bpp, &g->textures.weapon.image[WEAPON_SHOTGUN][i].line_length,
				&g->textures.weapon.image[WEAPON_SHOTGUN][i].endian);
		if (!g->textures.weapon.image[WEAPON_SHOTGUN][i].addr)
			return (cub_errors_setter(g, "Failed to get data addr of weapon xpm."));
	}
	// scaled_dimen.j = g->textures.weapon.dimension[WEAPON_SHOTGUN].j / 10;
	// scaled_dimen.i = g->textures.weapon.dimension[WEAPON_SHOTGUN].i / 10;
	// scale_img(g, scaled_dimen);
	g->textures.weapon.pos.x = HALF_WIN_WIDTH - g->textures.weapon.dimension[WEAPON_SHOTGUN].j / 2;
	g->textures.weapon.pos.y = WIN_HEIGHT - g->textures.weapon.dimension[WEAPON_SHOTGUN].i;
	return (RETURN_SUCCESS);
}