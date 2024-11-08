/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gholloco <gwendal.hollocou@orange.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 18:56:44 by gholloco          #+#    #+#             */
/*   Updated: 2024/11/04 03:53:23 by gholloco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	export_parse(char *line)
{
	int	i;

	i = 1;
	if (!line || !line[0] || (!ft_isalpha(line[0]) && line[0] != '_'))
		return (1);
	while (line[i])
	{
		if (line[i] == '=')
			return (0);
		while (!ft_isalnum(line[i]) && line[i] != '_')
			return (1);
		i++;
	}
	return (2);
}

int	variable_exist(t_env **env, char *variable, char *value)
{
	t_env	*node;

	node = *env;
	while (node)
	{
		if (ft_strncmp(node->variable, variable,
				ft_strlen(variable) + 1) == 0)
		{
			free(node->value);
			free(variable);
			node->value = value;
			return (1);
		}
		node = node->next;
	}
	return (0);
}

int	known_export(t_env **env, char *variable, char *value)
{
	char	*var;
	char	*val;

	var = ft_strdup(variable);
	val = ft_strdup(value);
	if (variable_exist(env, var, val))
		return (0);
	add_back_env(env, var, val);
	return (0);
}

int	export(t_env **env, char *line)
{
	char	**splitted;
	int		parse;

	parse = export_parse(line);
	if (parse == 1)
	{
		write(2, "export: '", 9);
		ft_putstr_fd(line, 2);
		write(2, "' : not a valid identifier\n", 27);
		return (1);
	}
	else if (parse == 2)
		return (0);
	splitted = split_in_two(line, '=');
	if (!splitted)
		return (1);
	if (variable_exist(env, splitted[0], splitted[1]))
	{
		return (free(splitted), 0);
	}
	add_back_env(env, splitted[0], splitted[1]);
	free(splitted);
	return (0);
}

int	ft_export(t_env **env, char **line, int old_exit_code)
{
	int	i;
	int	ret;

	i = 0;
	while (line[i])
	{
		ret = export(env, line[i]);
		i++;
	}
	if (old_exit_code)
		return (old_exit_code);
	return (ret);
}
