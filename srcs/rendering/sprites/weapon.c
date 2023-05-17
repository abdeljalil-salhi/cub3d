#include "cub3d.h"

int	cub_init_weapon(t_game *g)
{
	// t_iterators	scaled_dimen;
	t_iterators	it;

	g->textures.weapon.type = WEAPON_KNIFE;
	g->textures.weapon.frame = 0;

	g->textures.weapon.path[WEAPON_KNIFE][0] = "assets/sprites/weapon/knife/0.xpm";
	g->textures.weapon.path[WEAPON_KNIFE][1] = "assets/sprites/weapon/knife/1.xpm";
	g->textures.weapon.path[WEAPON_KNIFE][2] = "assets/sprites/weapon/knife/2.xpm";
	g->textures.weapon.path[WEAPON_KNIFE][3] = "assets/sprites/weapon/knife/3.xpm";
	g->textures.weapon.n_of_frames[WEAPON_KNIFE] = WEAPON_KNIFE_FRAMES;
	g->textures.weapon.frame_rate[WEAPON_KNIFE] = 80;
	g->textures.weapon.damage[WEAPON_KNIFE] = 10;
	g->textures.weapon.range[WEAPON_KNIFE] = 100.0f;
	g->textures.weapon.sound[WEAPON_KNIFE] = SOUND_KNIFE;
	g->textures.weapon.collected[WEAPON_KNIFE] = true;

	g->textures.weapon.path[WEAPON_SHOTGUN][0] = "assets/sprites/weapon/shotgun/0.xpm";
	g->textures.weapon.path[WEAPON_SHOTGUN][1] = "assets/sprites/weapon/shotgun/1.xpm";
	g->textures.weapon.path[WEAPON_SHOTGUN][2] = "assets/sprites/weapon/shotgun/2.xpm";
	g->textures.weapon.path[WEAPON_SHOTGUN][3] = "assets/sprites/weapon/shotgun/3.xpm";
    g->textures.weapon.path[WEAPON_SHOTGUN][4] = "assets/sprites/weapon/shotgun/4.xpm";
	g->textures.weapon.path[WEAPON_SHOTGUN][5] = "assets/sprites/weapon/shotgun/5.xpm";
	g->textures.weapon.n_of_frames[WEAPON_SHOTGUN] = WEAPON_SHOTGUN_FRAMES;
	g->textures.weapon.frame_rate[WEAPON_SHOTGUN] = 80;
	g->textures.weapon.damage[WEAPON_SHOTGUN] = 30;
	g->textures.weapon.range[WEAPON_SHOTGUN] = 300.0f;
	g->textures.weapon.sound[WEAPON_SHOTGUN] = SOUND_SHOTGUN;
	g->textures.weapon.collected[WEAPON_SHOTGUN] = false;

	it.i = -1;
	while (++it.i < N_OF_WEAPONS)
	{
		it.j = -1;
		while (++it.j < g->textures.weapon.n_of_frames[it.i])
		{
			g->textures.weapon.image[it.i][it.j].ref = mlx_xpm_file_to_image(g->mlx,
					g->textures.weapon.path[it.i][it.j],
					&g->textures.weapon.dimension[it.i].j,
					&g->textures.weapon.dimension[it.i].i);
			if (!g->textures.weapon.image[it.i][it.j].ref)
				return (cub_errors_setter(g, "Failed to load weapon xpm."));
			g->textures.weapon.image[it.i][it.j].addr = mlx_get_data_addr(g->textures.weapon.image[it.i][it.j].ref,
					&g->textures.weapon.image[it.i][it.j].bpp, &g->textures.weapon.image[it.i][it.j].line_length,
					&g->textures.weapon.image[it.i][it.j].endian);
			if (!g->textures.weapon.image[it.i][it.j].addr)
				return (cub_errors_setter(g, "Failed to get data addr of weapon xpm."));
		}
	}
	// scaled_dimen.j = g->textures.weapon.dimension[WEAPON_SHOTGUN].j / 10;
	// scaled_dimen.i = g->textures.weapon.dimension[WEAPON_SHOTGUN].i / 10;
	// scale_img(g, scaled_dimen);
	g->textures.weapon.pos.x = HALF_WIN_WIDTH - g->textures.weapon.dimension[WEAPON_SHOTGUN].j / 2;
	g->textures.weapon.pos.y = WIN_HEIGHT - g->textures.weapon.dimension[WEAPON_SHOTGUN].i;
	return (RETURN_SUCCESS);
}

int	get_object_type(int z)
{
	if (z == OBJECT_WEAPON_SHOTGUN)
		return (WEAPON_SHOTGUN);
	return (0);
}

bool	check_for_weapon_drops(t_game *g, int z)
{
	float	distance;

	if (g->objects[z].display)
	{
		distance = sqrt(pow(g->player.pos.x - g->objects[z].pos.x, 2) + pow(g->player.pos.y - g->objects[z].pos.y, 2));
		if (distance < 50.0f)
		{
			g->textures.weapon.type = get_object_type(g->objects[z].type);
			g->objects[z].display = false;
			g->textures.weapon.collected[g->textures.weapon.type] = true;
			return (false);
		}
		return (true);
	}
	return (false);
}
