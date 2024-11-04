/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gholloco <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 15:50:47 by gholloco          #+#    #+#             */
/*   Updated: 2023/11/10 15:33:24 by gholloco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	int_size(int nb)
{
	int			size;
	long int	n;

	n = (long int) nb;
	size = 0;
	if (n < 0)
		n *= -1;
	while (n > 0)
	{
		n /= 10;
		size += 1;
	}
	return (size);
}

static char	*fill_array(char *array, long int nb, int neg, int size_int)
{
	if (nb < 0)
	{
		array[0] = '-';
		size_int += 1;
	}
	while (nb != 0)
	{
		array[--size_int] = (nb * neg) % 10 + 48;
		nb /= 10;
	}
	return (array);
}

char	*ft_itoa(int n)
{
	char		*array;
	long int	nb;
	int			neg;
	int			size_int;

	if (n == 0)
		return (ft_strdup("0"));
	nb = (long int) n;
	neg = 1;
	size_int = int_size(n);
	n = 0;
	if (nb < 0)
	{
		neg = -1;
		n = 1;
	}
	array = malloc(size_int + 1 + n);
	if (array == NULL)
		return (NULL);
	array[size_int + n] = 0;
	return (fill_array(array, nb, neg, size_int));
}
