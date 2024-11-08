/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gholloco <gwendal.hollocou@orange.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 03:56:11 by gholloco          #+#    #+#             */
/*   Updated: 2024/11/04 03:56:22 by gholloco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exec_builtin(t_data *data, t_cmd *tmp)
{
	if (!ft_strncmp("echo", tmp->args[0], 5))
		data->exit_code = ft_echo(tmp->args + 1);
	else if (!ft_strncmp("pwd", tmp->args[0], 4))
		data->exit_code = ft_pwd();
	else if (!ft_strncmp("env", tmp->args[0], 4))
		data->exit_code = ft_env(&(data->env));
}
