/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 22:40:17 by absalhi           #+#    #+#             */
/*   Updated: 2023/03/19 22:55:42 by absalhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	cub_free_double_ptr(void **tab)
{
	int	i;

	i = -1;
	while (tab[++i])
		cub_free(tab[i]);
	cub_free(tab);
	return (RETURN_DEFAULT);
}

int	cub_free_double_int(int **tab, size_t size)
{
	int	i;

	i = -1;
	while ((size_t)++i < size)
		cub_free(tab[i]);
	cub_free(tab);
	return (RETURN_DEFAULT);
}

int	cub_free(void *ptr)
{
	free(ptr);
	return (RETURN_DEFAULT);
}
