/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gholloco <gwendal.hollocou@orange.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 04:24:54 by gholloco          #+#    #+#             */
/*   Updated: 2023/11/10 16:24:47 by gholloco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (*(s + i))
	{
		if ((unsigned char) *(s + i) == (char) c)
			return ((char *)(s + i));
		i++;
	}
	if ((unsigned char) *(s + i) == (char) c)
		return ((char *)(s + i));
	return (NULL);
}
