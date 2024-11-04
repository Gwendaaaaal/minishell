/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gholloco <gwendal.hollocou@orange.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 19:58:41 by gholloco          #+#    #+#             */
/*   Updated: 2024/11/03 22:33:44 by gholloco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// n_flag = 1 -> -n
// return 0 == all good
// return 1 == no args
int	ft_echo(char **args)
{
	int	i;
	int n_flag;

	i = 0;
	n_flag = 0;
	if (args[0] && !ft_strncmp(args[0], "-n", 3))
	{
		n_flag = 1;
		args = args + 1;
	}
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
