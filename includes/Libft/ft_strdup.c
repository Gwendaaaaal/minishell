/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gholloco <gwendal.hollocou@orange.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 06:28:09 by gholloco          #+#    #+#             */
/*   Updated: 2023/11/10 15:06:32 by gholloco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcpy(char *dest, char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}

char	*ft_strdup(const char *src)
{
	char	*tab;

	tab = NULL;
	if (!src)
		return (tab);
	tab = malloc(sizeof(char) * ft_strlen(src) + 1);
	if (tab == NULL)
		return (tab);
	ft_strlcpy(tab, src, ft_strlen(src) + 1);
	return (tab);
}
