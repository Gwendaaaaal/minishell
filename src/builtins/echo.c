/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gholloco <gwendal.hollocou@orange.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 19:58:41 by gholloco          #+#    #+#             */
/*   Updated: 2024/11/07 23:59:11 by gholloco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**skip_n_flags(char **args, int *n_flag)
{
	int	i;
	int	j;

	i = 0;
	while (args[i])
	{
		j = 0;
		if (args[i][j] == '-')
		{
			j++;
			while (args[i][j] && args[i][j] == 'n')
				j++;
			if (args[i][j] == '\0')
				*n_flag = 1;
			else
				return (args + i);
		}
		else
			return (args + i);
		i++;
	}
	return (args + i);
}

int	ft_echo(char **args)
{
	int	i;
	int	n_flag;

	i = 0;
	n_flag = 0;
	args = skip_n_flags(args, &n_flag);
	while (args[i])
	{
		if (i)
			printf(" ");
		printf("%s", args[i]);
		i++;
	}
	if (!n_flag)
		printf("\n");
	return (0);
}
