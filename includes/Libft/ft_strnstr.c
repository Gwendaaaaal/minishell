/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gholloco <gwendal.hollocou@orange.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 10:59:10 by gholloco          #+#    #+#             */
/*   Updated: 2023/11/10 15:35:03 by gholloco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t		i;
	size_t		found;
	char		*temp;

	temp = (char *) big;
	i = 0;
	found = 0;
	if (ft_strlen(little) == 0)
		return (temp);
	while (i < len && big[i])
	{
		found = 0;
		while (i + found < len && big[i + found] == little[found]
			&& big[i + found] && little[found])
		{		
			found++;
			if (found == ft_strlen(little))
				return (temp + i);
		}
		i++;
	}
	return (NULL);
}
