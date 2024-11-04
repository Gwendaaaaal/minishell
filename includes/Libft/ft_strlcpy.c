/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gholloco <gwendal.hollocou@orange.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 12:03:25 by gholloco          #+#    #+#             */
/*   Updated: 2023/11/08 19:07:52 by gholloco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t sz)
{
	int	i;

	i = 0;
	if (sz == 0)
		return (ft_strlen(src));
	while (sz > 1 && src[i])
	{
		dst[i] = src[i];
		i++;
		sz--;
	}
	dst[i] = '\0';
	return (ft_strlen(src));
}
