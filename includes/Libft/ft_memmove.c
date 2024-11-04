/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gholloco <gwendal.hollocou@orange.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 16:28:07 by gholloco          #+#    #+#             */
/*   Updated: 2023/11/10 14:53:17 by gholloco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*ptr;

	if (!dest && !src)
		return (NULL);
	if (src > dest)
		ft_memcpy(dest, src, n);
	else
	{
		ptr = (char *) dest;
		while (n-- > 0)
			ptr[n] = ((char *) src)[n];
	}
	return (dest);
}
