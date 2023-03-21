/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 20:14:15 by absalhi           #+#    #+#             */
/*   Updated: 2023/03/20 23:30:42 by absalhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_is_delimiter(char c, char const *charset)
{
	int	i;

	i = -1;
	while (charset[++i])
		if (c == charset[i])
			return (1);
	return (0);
}

static int	ft_countwords(char const *s, char const *charset)
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
		if (!ft_is_delimiter(s[i], charset))
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

static char	*ft_strdupi(const char *s, char const *set, unsigned int *index)
{
	char	*minitab;
	int		i;
	int		len;

	len = 0;
	i = (*index) - 1;
	while (s[++i] && !ft_is_delimiter(s[i], set))
		len++;
	minitab = (char *) ft_calloc(len + 1, sizeof(char));
	if (!minitab)
		return (NULL);
	i = 0;
	while (s[(*index)] && !ft_is_delimiter(s[(*index)], set))
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

char	**ft_split(char const *s, char const *charset)
{
	char			**tab;
	int				words;
	int				current;
	unsigned int	i;

	words = ft_countwords(s, charset);
	tab = (char **) ft_calloc(words + 1, sizeof(char *));
	if (!tab)
		return (NULL);
	current = 0;
	i = 0;
	while (s && current < words)
	{
		while (s[i] && ft_is_delimiter(s[i], charset))
			if (!s[i++])
				break ;
		tab[current] = ft_strdupi(s, charset, &i);
		if (!tab[current++])
		{
			ft_freetab(tab);
			return (NULL);
		}
	}
	return (tab);
}
