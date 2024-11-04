/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gholloco <gwendal.hollocou@orange.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 05:58:29 by gholloco          #+#    #+#             */
/*   Updated: 2024/11/01 05:21:57 by gholloco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	error_exit(char *msg)
{
	printf("%s\n", msg);
	exit(0);
}

void	ft_free_cmd(t_data *data)
{
	int		i;
	t_cmd	*tmp;

	i = 0;
	if (data->pid[0] && data->pid[0] != -1)
		close (data->pid[0]);
	if (data->pid[1] && data->pid[1] != -1)
		close (data->pid[1]);
	while (data->cmd != NULL)
	{
		if (data->cmd->next == NULL && (data->cmd->infile == -1 || data->cmd->outfile == -1))
			data->exit_code = 1;
		while (data->cmd->args[i])
		{
			free (data->cmd->args[i]);
			i++;
		}
		free (data->cmd->args);
		tmp = data->cmd;
		data->cmd = data->cmd->next;
		free (tmp);
		i = 0;
	}
	free (data->cmd);
}

void	free_all(t_data *data, char *error, int ext)
{
	char *tmp;

	tmp = ft_itoa(data->exit_code);
	known_export(&(data->env), "?", tmp);
	free(tmp);
	if (error)
		printf("%s\n", error);
	if (data->cmd)
		ft_free_cmd(data);
	if (data->readline)
		free (data->readline);
	if (data->env)
		free_env(&data->env);
	if (data->pid[0] && data->pid[0] != -1)
		close (data->pid[0]);
	if (data->pid[1] && data->pid[1] != -1)
		close (data->pid[1]);
	if (!access(".heredoc.tmp", F_OK))
		unlink(".heredoc.tmp");
	if (data)
		free (data);
	if (ext != -1)
		exit(ext);
}
