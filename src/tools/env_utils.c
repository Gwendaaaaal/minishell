/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gholloco <gwendal.hollocou@orange.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 02:48:36 by gholloco          #+#    #+#             */
/*   Updated: 2024/10/31 03:30:57 by gholloco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char** get_env_refreshed(t_env **env)
{
	char	**env_char;
	char	*tmp_char;
	t_env	*tmp; 
	int		i;

	i = 0;
	tmp = *env;
	env_char = malloc(sizeof(char *) * (get_env_length(env) + 1));
	while (tmp)
	{
		tmp_char = ft_strdup("");
		env_char[i] = ft_strjoin(tmp_char, tmp->variable);
		free(tmp_char);
		env_char[i] = ft_strappend(env_char[i], '=');
		tmp_char = env_char[i];
		env_char[i] = ft_strjoin(tmp_char, tmp->value);
		free(tmp_char);
		
		tmp = tmp->next;
		i++;
	}
	env_char[i] = NULL;
	
	return (env_char);
}
