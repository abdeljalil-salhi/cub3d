/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 17:07:36 by absalhi           #+#    #+#             */
/*   Updated: 2022/11/30 13:51:29 by absalhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*get_next_line(int fd)
{
	char		*line;
	static char	*stash[512];

	if (fd < 0 || BUFFER_SIZE < 1 || read(fd, &line, 0) < 0 || fd > 512)
		return (NULL);
	stash[fd] = ft_read_and_add_to_stash(fd, stash[fd]);
	if (!stash[fd])
		return (NULL);
	line = ft_extract_line(stash[fd]);
	stash[fd] = ft_extract_remaining(stash[fd]);
	return (line);
}

char	*ft_read_and_add_to_stash(int fd, char *stash)
{
	char	*buf;
	int		readed;

	buf = (char *) ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buf)
		return (NULL);
	readed = 1;
	while (!ft_strchr(stash, 10) && readed)
	{
		readed = read(fd, buf, BUFFER_SIZE);
		if (readed == -1)
		{
			free(buf);
			return (NULL);
		}
		buf[readed] = 0;
		stash = ft_nullstrjoin(stash, buf);
	}
	free(buf);
	return (stash);
}

char	*ft_extract_line(char *stash)
{
	char	*line;
	size_t	len;
	int		i;

	if (!(*stash))
		return (NULL);
	len = 0;
	while (stash[len] && stash[len] != 10)
		len++;
	line = (char *) ft_calloc(len + 2, sizeof(char));
	if (!line)
		return (NULL);
	i = -1;
	while (stash[++i] && stash[i] != 10)
		line[i] = stash[i];
	if (stash[i] == 10)
	{
		line[i] = stash[i];
		i++;
	}
	line[i] = 0;
	return (line);
}

char	*ft_extract_remaining(char *stash)
{
	char	*tmp;
	size_t	to_save;
	size_t	to_clear;

	to_clear = 0;
	while (stash[to_clear] && stash[to_clear] != 10)
		to_clear++;
	if (!stash[to_clear])
	{
		free(stash);
		return (NULL);
	}
	tmp = (char *) ft_calloc(ft_strlen(stash) - to_clear + 1, sizeof(char));
	if (!tmp)
		return (NULL);
	to_clear++;
	to_save = 0;
	while (stash[to_clear])
		tmp[to_save++] = stash[to_clear++];
	tmp[to_save] = 0;
	free(stash);
	return (tmp);
}
