/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_open.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 00:43:08 by absalhi           #+#    #+#             */
/*   Updated: 2023/05/19 09:42:48 by absalhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	file_open(t_game *g, int *fd, char *filename)
{
	*fd = open(filename, O_RDONLY);
	if (*fd == -1)
	{
		if (errno == EACCES)
			return (errors_setter(g, FILE_PERMISSION_DENIED));
		else if (errno == ENOENT)
			return (errors_setter(g, FILE_NOT_FOUND));
		else
			return (errors_setter(g, FILE_UNKNOWN_ERROR));
	}
	return (RETURN_SUCCESS);
}
