/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gholloco <gwendal.hollocou@orange.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 16:28:07 by gholloco          #+#    #+#             */
/*   Updated: 2023/11/10 14:52:36 by gholloco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char	*ptr;

	if (!dest && !src)
		return (NULL);
	ptr = (char *) dest;
	while (n > 0)
	{
		*ptr = *((char *) src);
		ptr++;
		src++;
		n--;
	}
	return (dest);
}
