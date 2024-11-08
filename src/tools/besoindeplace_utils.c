/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   besoindeplace_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gholloco <gwendal.hollocou@orange.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 23:02:05 by gholloco          #+#    #+#             */
/*   Updated: 2024/11/04 04:07:10 by gholloco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	close_both_pid(int pid1, int pid2)
{
	close(pid1);
	close(pid2);
	return ;
}

void	check_dir(char **path, char *cmd, t_data *data)
{
	struct stat	path_stat;

	stat(*path, &path_stat);
	if (!S_ISREG(path_stat.st_mode))
	{
		write(2, cmd, ft_strlen(cmd));
		write(2, " : Is a directory\n", 18);
		data->exit_code = 126;
		free_all(data, NULL, data->exit_code);
	}
	return ;
}

t_env	*add_back_env(t_env **env, char *variable, char *value)
{
	t_env	*node;
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!env || !new)
		return (NULL);
	new->variable = variable;
	new->value = value;
	new->next = NULL;
	node = *env;
	if (!*env)
	{
		*env = new;
		return (new);
	}
	while (node->next)
		node = node->next;
	node->next = new;
	return (new);
}

void	skip_cmd(t_cmd **tmp, t_data *data)
{
	while ((*tmp) != NULL && ((*tmp)->infile == -1 || (*tmp)->outfile == -1))
	{
		if ((*tmp)->next && (*tmp)->next->infile < 0
			&& (!ft_strncmp((*tmp)->args[0], "cat", 4)
				&& !ft_strncmp((*tmp)->next->args[0], "cat", 4)))
		{
			data->exit_code = 0;
			(*tmp) = (*tmp)->next;
		}
		(*tmp) = (*tmp)->next;
	}
}
