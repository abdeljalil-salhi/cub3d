/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 21:40:50 by absalhi           #+#    #+#             */
/*   Updated: 2023/03/21 11:09:18 by absalhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	cub_print_parsing(t_game *g)
{
	(void) g;
	printf("");
}

int	main(int argc, char **argv)
{
	t_game	g;

	ft_bzero(&g, sizeof(t_game));
	if (argc != 2)
		cub_errors_exit(&g, "\tUsage:\t./cub3D [filename].cub");
	if (cub_parser(&g, argv[1]))
		cub_errors_exit(&g, g.error.message);
	if (LEAKS)
		system("leaks cub3D");
	
	return (EXIT_SUCCESS);
}
