/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 20:14:15 by absalhi           #+#    #+#             */
/*   Updated: 2022/10/15 17:31:58 by absalhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_countwords(char const *s, char delimiter)
{
	int	i;
	int	new;
	int	words;

	if (!s)
		return (0);
	words = 0;
	new = 1;
	i = -1;
	while (s[++i])
	{
		if (s[i] != delimiter)
		{
			if (new)
				words++;
			new = 0;
		}
		else
			new = 1;
	}
	return (words);
}

static char	*ft_strdupi(const char *s, char c, unsigned int *index)
{
	char	*minitab;
	int		i;
	int		len;

	len = 0;
	i = (*index) - 1;
	while (s[++i] && s[i] != c)
		len++;
	minitab = (char *) ft_calloc(len + 1, sizeof(char));
	if (!minitab)
		return (NULL);
	i = 0;
	while (s[(*index)] && s[(*index)] != c)
		minitab[i++] = s[(*index)++];
	return (minitab);
}

static void	ft_freetab(char **tab)
{
	int	i;

	i = -1;
	while (tab[++i])
		free(tab[i]);
	free(tab);
}

char	**ft_split(char const *s, char c)
{
	char			**tab;
	int				words;
	int				current;
	unsigned int	i;

	words = ft_countwords(s, c);
	tab = (char **) ft_calloc(words + 1, sizeof(char *));
	if (!tab)
		return (NULL);
	current = 0;
	i = 0;
	while (s && current < words)
	{
		while (s[i] && s[i] == c)
			if (!s[i++])
				break ;
		tab[current] = ft_strdupi(s, c, &i);
		if (!tab[current++])
		{
			ft_freetab(tab);
			return (NULL);
		}
	}
	return (tab);
}
