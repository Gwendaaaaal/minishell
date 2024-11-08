/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_form.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gholloco <gwendal.hollocou@orange.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 06:00:51 by gholloco          #+#    #+#             */
/*   Updated: 2024/11/06 15:04:24 by gholloco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_cmd	*ft_cmdnew(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->args = NULL;
	cmd->infile = -2;
	cmd->outfile = -2;
	cmd->next = NULL;
	return (cmd);
}

int	size_dtab(t_list *tmp)
{
	int	i;

	i = 0;
	while (tmp != NULL && tmp->token != 4)
	{
		if (tmp->token < 4)
			i++;
		tmp = tmp->next;
	}
	return (i);
}

char	**args_in_tab(t_list *tmp)
{
	char	**args;
	int		i;

	args = malloc (sizeof(char *) * (size_dtab(tmp) + 1));
	i = 0;
	while (tmp != NULL && tmp->token != 4)
	{
		if (tmp->token < 4)
		{
			args[i] = ft_strdup(tmp->content);
			i++;
		}
		tmp = tmp->next;
	}
	args[i] = NULL;
	return (args);
}

void	list_to_tab(t_list *parse, t_cmd *cmd)
{
	t_list	*tmp;
	t_cmd	*tcmd;

	tmp = parse;
	while (tmp != NULL)
	{
		tcmd = cmd;
		tcmd->args = args_in_tab(tmp);
		while (tmp != NULL)
		{
			if (tmp->token != 4)
				tmp = tmp->next;
			else
				break ;
		}
		if (tmp != NULL && tmp->token == 4)
		{
			tcmd = ft_cmdnew();
			ft_cmdadd_back(&cmd, tcmd);
			cmd = cmd->next;
			tmp = tmp->next;
		}
	}
}

void	make_cmd(t_data *data)
{
	if (!ft_strlen(data->readline))
		return ;
	if (last_pipe(data->parse) == 1)
	{
		ft_freelist(data->parse);
		write(2, "syntax error : pipe at start or end of cmd\n", 43);
		data->exit_code = 2;
		return ;
	}
	data->cmd = malloc(sizeof(t_cmd));
	data->cmd->infile = -2;
	data->cmd->outfile = -2;
	data->cmd->next = NULL;
	list_to_tab(data->parse, data->cmd);
	fd_to_tab(data);
	ft_freelist(data->parse);
	exec_cmd(data);
}
