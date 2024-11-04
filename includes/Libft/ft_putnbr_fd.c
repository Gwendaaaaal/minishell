/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gholloco <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 14:08:38 by gholloco          #+#    #+#             */
/*   Updated: 2023/11/10 15:35:19 by gholloco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char			output;
	long long int	bigint;

	bigint = (long long int) n;
	if (bigint < 0)
	{
		write(fd, "-", 1);
		bigint = -bigint;
	}
	if (bigint / 10 > 0)
		ft_putnbr_fd(bigint / 10, fd);
	output = (bigint % 10) + 48;
	ft_putchar_fd(output, fd);
}
