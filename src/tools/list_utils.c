/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gholloco <gwendal.hollocou@orange.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 05:57:34 by gholloco          #+#    #+#             */
/*   Updated: 2024/11/04 02:37:51 by gholloco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	last_pipe(t_list *parse)
{
	t_list	*tmp;

	tmp = parse;
	if (tmp->token == 4)
		return (1);
	while (tmp != NULL)
	{
		if (tmp->next == NULL)
			if (tmp->token == 4)
				return (1);
		tmp = tmp->next;
	}
	return (0);
}

void	ft_freelist(t_list *tab)
{
	t_list	*tmp;
	t_list	*stmp;

	tmp = tab;
	while (tmp != NULL)
	{
		stmp = tmp;
		free (stmp->content);
		tmp = tmp->next;
		free (stmp);
	}
}

void	ft_cmdadd_back(t_cmd **lst, t_cmd *new)
{
	t_cmd	*node;

	if (!lst || !new)
		return ;
	node = *lst;
	if (!node)
	{
		*lst = new;
		return ;
	}
	while (node->next)
		node = node->next;
	node->next = new;
}

void	ft_print_tab(t_cmd *cmd)
{
	int		i;
	t_cmd	*tmp;

	i = 0;
	while (cmd != NULL)
	{
		while (cmd->args[i])
		{
			//printf("%s", cmd->args[i]);
			//printf("%i", cmd->infile);
			//printf("%i", cmd->outfile);
			free (cmd->args[i]);
			i++;
		}
		free (cmd->args);
		tmp = cmd;
		cmd = cmd->next;
		free (tmp);
		i = 0;
		/*while (cmd->args[i])
		{
			free (cmd->args[i]);
			i++;
		}
		free(cmd->args);
		tmp = cmd;
		cmd = cmd->next;
		free (tmp);
		i = 0;*/
	}
	free (cmd);
}

void	ft_print_list_no_free(t_env **env)
{
	t_env *node;

	node = *env;
	while (node)
	{
		printf("variable = %s, value = %s\n", node->variable, node->value);
		node = node->next;
	}
}

void	ft_printlist(t_list *tab)
{
	t_list	*tmp;
	t_list	*stmp;

	tmp = tab;
	while (tmp != NULL)
	{
		printf("%s  ", tmp->content);
		printf("%d\n", tmp->token);
		tmp = tmp->next;
	}
	tmp = tab;
	while (tmp != NULL)
	{
		free (tmp->content);
		stmp = tmp;
		tmp = tmp->next;
		free (stmp);
	}
}
