/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gholloco <gwendal.hollocou@orange.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 12:44:55 by gholloco          #+#    #+#             */
/*   Updated: 2024/10/31 01:41:33 by gholloco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_data	*init_data(char **envp)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->env = NULL;
	data->env_char = envp;
	while (*envp)
		export(&(data->env), *envp++);
	data->cmd = NULL;
	data->parse = NULL;
	data->prompt = "minishell >";
	data->readline = NULL;
	data->pid[0] = -1;
	data->pid[1] = -1;
	data->exit_code = 0;
	return (data);
}
