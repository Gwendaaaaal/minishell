/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gholloco <gwendal.hollocou@orange.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 12:06:29 by gholloco          #+#    #+#             */
/*   Updated: 2024/10/31 03:06:35 by gholloco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_env_node(t_env *node)
{
	free(node->variable);
	free(node->value);
	free(node);
}

void	free_env(t_env **env)
{
	t_env	*node;
	t_env	*del;

	node = *env;
	while (node)
	{
		del = node;
		node = node->next;
		free_env_node(del);
	}
}

char	*get_env_variable(t_env **env, char *variable)
{
	t_env	*node;

	node = *env;
	while (node)
	{
		if (!ft_strncmp(node->variable, variable, ft_strlen(node->variable)))
			return (ft_strdup(node->value));
		node = node->next;
	}
	return (ft_strdup(""));
}

int	get_env_length(t_env **env)
{
	t_env	*node;
	int		i;

	node = *env;
	i = 0;
	while (node)
	{
		node = node->next;
		i++;
	}
	return (i);
}

int	ft_env(t_env **env)
{
	t_env	*node;

	node = *env;
	while (node)
	{
		printf("%s=%s\n", node->variable, node->value);
		node = node->next;
	}
	return (0);
}
