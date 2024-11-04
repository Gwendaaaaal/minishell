/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gholloco <gwendal.hollocou@orange.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 11:58:25 by gholloco          #+#    #+#             */
/*   Updated: 2024/10/31 01:35:33 by gholloco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// ATROCE A REFAIRE
// return 0 == all good
// return 1 == wrong args
// return 2 == no variable to unset
// int	unset(t_env **env, char *variable)
// {
// 	t_env	*node;
// 	t_env	*del;
//
// 	if (!env || !variable)
// 		return (1);
// 	node = *env;
// 	while (node && node->next && ft_strncmp(node->next->variable, variable,
// 			ft_strlen(node->next->variable)))
// 		node = node->next;
// 	if (!node)
// 		return (2);
// 	del = node->next;
// 	node->next = del->next;
// 	free_env_node(del);
// 	return (0);
// }

int	unset(t_env **env, char *variable)
{
	t_env	*node;
	t_env	*temp;

	if (ft_strncmp((*env)->variable, variable,
			ft_strlen((*env)->variable)) == 0)
	{
		temp = *env;
		*env = (*env)->next;
		free_env_node(temp);
		return (0);
	}
	node = *env;
	while (node && node->next)
	{
		if (ft_strncmp(node->next->variable, variable,
				ft_strlen(node->next->variable)) == 0)
		{
			temp = node->next;
			node->next = temp->next;
			free_env_node(temp);
			return (0);
		}
		node = node->next;
	}
	return (0);
}

int	ft_unset(t_env **env, char **variable)
{
	int	i;

	i = 0;
	while (variable[i])
	{
		unset(env, variable[i]);
		i++;
	}
	return (0);
}
