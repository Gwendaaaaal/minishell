/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gholloco <gwendal.hollocou@orange.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 05:46:16 by gholloco          #+#    #+#             */
/*   Updated: 2023/11/08 15:01:15 by gholloco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	int	i;

	i = 0;
	while (n > 0 && (s1[i] || s2[i]))
	{
		if (s1[i] != s2[i])
			return (((unsigned char) s1[i]) - ((unsigned char) s2[i]));
		n--;
		i++;
	}
	return (0);
}
