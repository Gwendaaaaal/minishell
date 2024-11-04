/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gholloco <gwendal.hollocou@orange.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 02:21:44 by gholloco          #+#    #+#             */
/*   Updated: 2024/11/04 00:07:48 by gholloco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_strjoin_with_free(char *s1, char const *s2)
{
	int		i;
	int		j;
	int		index;
	char	*joined;

	i = 0;
	j = 0;
	index = 0;
	if (!s1 || !s2)
		return (NULL);
	joined = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!joined)
		return (NULL);
	while (s1[i])
		joined[index++] = s1[i++];
	while (s2[j])
		joined[index++] = s2[j++];
	joined[index] = 0;
	free(s1);
	return (joined);
}

char	*ft_strjoin_with_double_free(char *s1, char *s2)
{
	int		i;
	int		j;
	int		index;
	char	*joined;

	i = 0;
	j = 0;
	index = 0;
	if (!s1 || !s2)
		return (NULL);
	joined = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!joined)
		return (NULL);
	while (s1[i])
		joined[index++] = s1[i++];
	while (s2[j])
		joined[index++] = s2[j++];
	joined[index] = 0;
	free(s1);
	free(s2);
	return (joined);
}

char	*ft_strappend(char *string, char c)
{
	int		len;
	char	*res;

	len = ft_strlen(string);
	res = malloc((len + 2) * sizeof(char));
	ft_strlcpy(res, string, len + 1);
	res[len] = c;
	res[len + 1] = '\0';
	free(string);
	return (res);
}
