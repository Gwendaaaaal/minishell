/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gholloco <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 13:53:23 by gholloco          #+#    #+#             */
/*   Updated: 2024/10/15 19:45:04 by gholloco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
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
	return (joined);
}
