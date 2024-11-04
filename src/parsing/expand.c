/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gholloco <gwendal.hollocou@orange.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 15:51:27 by gholloco          #+#    #+#             */
/*   Updated: 2024/11/04 00:00:42 by gholloco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*rm_quotes(char *string)
{
	int		i;
	int		quote;
	char	*ret;

	i = 0;
	quote = 0;
	ret = ft_strdup("");
	while (string[i])
	{
		if (quote == 0 && (string[i] == '\'' || string[i] == '"'))
			quote = string[i++];
		else if (quote && string[i] == quote)
		{
			quote = 0;
			i++;
		}
		else if (string[i])
		{
			ret = ft_strappend(ret, string[i]);
			i++;
		}
	}
	free(string);
	return (ret);
}

char	*string_till_exp(char *string, int *i, int *quote, int heredoc)
{
	char	*ret;
	int		tmp;
	int		cnt;

	tmp = *i;
	cnt = 0;
	while (string[*i])
	{
		if (string[*i] == '$' && *quote != '\'')
			break ;
		if (!heredoc && *quote == 0
			&& (string[*i] == '\'' || string[*i] == '"'))
			*quote = string[*i];
		else if (*quote == string[*i])
			*quote = 0;
		cnt++;
		(*i)++;
	}
	ret = malloc(sizeof(char) * (cnt + 1));
	ft_strlcpy(ret, string + tmp, cnt + 1);
	return (ret);
}

char	*expand_var(t_data *data, char *string, int *i)
{
	char	*var_name;
	char	*ret;
	int		cnt;
	int		tmp;

	cnt = 0;
	tmp = *i;
	if (string[*i + 1] == '?')
		return ((*i)++, (*i)++, ft_itoa(data->exit_code));
	if (!ft_isalnum(string[*i + 1]) && string[*i + 1] != '_')
	{
		(*i)++;
		return (ft_strdup("$"));
	}
	(*i)++;
	while (ft_isalnum(string[*i]) || string[*i] == '_')
	{
		(*i)++;
		cnt++;
	}
	var_name = malloc(sizeof(char) * (cnt + 1));
	ft_strlcpy(var_name, string + tmp + 1, cnt + 1);
	ret = get_env_variable(&(data->env), var_name);
	free(var_name);
	return (ret);
}

char	*expand(t_data *data, char *string, int heredoc)
{
	char	*joined;
	char	*tmp;
	int		squote;
	int		i;

	i = 0;
	squote = 0;
	joined = ft_strdup("");
	while (string[i])
	{
		tmp = string_till_exp(string, &i, &squote, heredoc);
		joined = ft_strjoin_with_double_free(joined, tmp);
		if (string[i])
		{
			tmp = expand_var(data, string, &i);
			joined = ft_strjoin_with_double_free(joined, tmp);
		}
	}
	if (heredoc)
		return (joined);
	return (rm_quotes(joined));
}

int	expand_parsing(t_data *data)
{
	t_list	*node;
	char	*tmp;

	node = data->parse;
	while (node)
	{
		tmp = expand(data, node->content, 0);
		free(node->content);
		node->content = tmp;
		node = node->next;
	}
	return (0);
}
