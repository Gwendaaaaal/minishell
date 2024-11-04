/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gholloco <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 17:21:47 by gholloco          #+#    #+#             */
/*   Updated: 2023/11/10 14:54:13 by gholloco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	int				i;
	unsigned char	*ptr;

	ptr = (unsigned char *) s;
	i = 0;
	while (n > 0)
	{
		if ((ptr[i]) == (unsigned char) c)
			return ((void *) s + i);
		i++;
		n--;
	}
	return (NULL);
}
