/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gholloco <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 13:55:34 by gholloco          #+#    #+#             */
/*   Updated: 2023/11/10 16:24:35 by gholloco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_strlen_till_sep(const char *str, char c, int offset)
{
	int	i;

	i = 0;
	while (str[offset] && str[offset] == c)
		offset++;
	while (str[offset] && str[offset] != c)
	{
		i++;
		offset++;
	}
	return (i);
}

static char	*write_in_tab_sep(const char *str, char c, int *offset, char *tab)
{
	int	i;

	i = 0;
	while (str[*offset] && str[*offset] == c)
		(*offset)++;
	while (str[*offset] && str[*offset] != c)
	{
		tab[i] = str[*offset];
		i++;
		(*offset)++;
	}
	tab[i] = 0;
	return (tab);
}

static int	count_words(const char *str, char c)
{
	int	i;
	int	cnt;

	i = 0;
	cnt = 0;
	if (ft_strlen(str) == 0)
		return (0);
	while (str[i])
	{
		while (str[i] && str[i] == c)
			i++;
		if (str[i] && str[i] != c
			&& (i == 0 || str[i - 1] == c))
			cnt++;
		while (str[i] && str[i] != c)
			i++;
	}
	return (cnt);
}

static char	**free_tab(char **tab, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		free(tab[i++]);
	}
	free(tab);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	int		nb_words;
	int		i;
	int		offset;
	int		len_str;

	if (!s)
		return (NULL);
	offset = 0;
	nb_words = count_words(s, c);
	i = 0;
	tab = malloc(sizeof(char *) * (nb_words + 1));
	if (tab == NULL)
		return (NULL);
	while (i < nb_words)
	{
		len_str = ft_strlen_till_sep(s, c, offset) + 1;
		tab[i] = malloc(sizeof(char) * len_str);
		if (tab[i] == NULL)
			return (free_tab(tab, i));
		write_in_tab_sep(s, c, &offset, tab[i]);
		i++;
	}
	tab[i] = 0;
	return (tab);
}
