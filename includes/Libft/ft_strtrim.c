/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gholloco <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 15:06:26 by gholloco          #+#    #+#             */
/*   Updated: 2023/11/10 15:29:20 by gholloco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_in_set(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int	start;
	int	end;
	int	index;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	end = ft_strlen(s1) - 1;
	while (s1[start] && is_in_set(s1[start], set))
		start++;
	index = start;
	while (s1[index] && !is_in_set(s1[index], set))
		index++;
	while (s1[end] && is_in_set(s1[end], set))
		end--;
	if (end - start < 0)
		return (ft_strdup(""));
	return (ft_substr(s1, start, end - start + 1));
}
