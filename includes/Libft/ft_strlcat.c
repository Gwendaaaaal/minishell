/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 04:39:08 by gholloco          #+#    #+#             */
/*   Updated: 2023/11/10 16:25:00 by gholloco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	ind;

	i = 0;
	j = 0;
	ind = 0;
	if (size == 0)
		return (ft_strlen(src));
	while (dst[i])
		i++;
	while (src[j])
		j++;
	if (size <= i)
		return (size + j);
	while (ind < j && ind + i < size - 1)
	{
		dst[i + ind] = src[ind];
		ind++;
	}
	dst[i + ind] = 0;
	return (i + j);
}
