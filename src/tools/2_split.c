/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_split.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gholloco <gwendal.hollocou@orange.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 00:33:07 by gholloco          #+#    #+#             */
/*   Updated: 2024/10/27 05:58:22 by gholloco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

static char	*write_in_tab(const char *str, char c, int *offset, char *tab)
{
	int	i;

	i = 0;
	while (str[*offset] && str[*offset] == c)
		(*offset)++;
	while (str[*offset])
	{
		tab[i] = str[*offset];
		i++;
		(*offset)++;
	}
	tab[i] = 0;
	return (tab);
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

char	**split_in_two(char const *s, char c)
{
	char	**tab;
	int		i;
	int		len_str;
	int		offset;

	tab = malloc(sizeof(char *) * 3);
	i = 0;
	offset = 0;
	len_str = ft_strlen_till_sep(s, c, offset) + 1;
	tab[0] = malloc(sizeof(char) * len_str);
	if (tab[0] == NULL)
		return (free_tab(tab, i));
	write_in_tab_sep(s, c, &offset, tab[0]);
	len_str = ft_strlen(s + offset) + 1;
	tab[1] = malloc(sizeof(char) * len_str);
	write_in_tab(s, '=', &offset, tab[1]);
	tab[2] = 0;
	return (tab);
}

// int	main(int argc, char **argv)
// {
// 	char **tab;
// 	int i = 0;
//
// 	tab = split_in_two("abcdefg=fasdfasdfasdfsad=fsadfaasd", '=');
// 	printf("%s\n", tab[0]);
// 	printf("%s\n", tab[1]);
// 	// while (tab[i])
// 	// 	printf("%s\n", tab[i++]);
// 	free(tab[0]);
// 	free(tab[1]);
// 	free(tab);
// 	return (0);
// }
