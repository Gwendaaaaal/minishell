/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_content.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gholloco <gwendal.hollocou@orange.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 05:53:03 by gholloco          #+#    #+#             */
/*   Updated: 2024/11/01 01:25:56 by gholloco         ###   ########.fr       */
/*                                                                            */

/* ************************************************************************** */

#include "../../includes/minishell.h"

void remove_first_node(t_data *data) 
{
    t_list *first_node;
    const char *content;

	if (!data->parse || !data->parse->next)
		return ;
	first_node = data->parse;
	content = first_node->content;
    while (*content) 
	{
        if (*content != ' ')
            return ;
        content++;
    }
    data->parse = first_node->next;
    free(first_node->content);
    free(first_node);
}

int	size_of_string(char *str, int j)
{
	int	dquote;
	int	quote;
	int	i;

	i = 0;
	quote = 0;
	dquote = 0;
	while (str[j])
	{
		if (str[j] == '\"' && dquote == 0 && quote == 0)
			dquote = 1;
		else if (str[j] == '\'' && quote == 0 && dquote == 0)
			quote = 1;
		else if (str[j] == '\"' && dquote == 1)
			dquote = 0;
		else if (str[j] == '\'' && quote == 1)
			quote = 0;
		else if ((str[j] == ' ' || str[j] == '|') && dquote == 0 && quote == 0)
			break ;
		j++;
		i++;
	}
	return (i);
}

int	string_to_tab(t_data *data, int i)
{
	t_list	*tab;
	char	*tmp;
	int		j;

	j = i;
	j = size_of_string(data->readline, j);
	tmp = malloc((j + 1) * sizeof(char));
	tab = NULL;
	ft_strlcpy(tmp, data->readline + i, j + 1);
	tab = ft_lstnew(tmp, 1);
	ft_lstadd_back(&(data->parse), tab);
	i = i + j;
	return (i);
}

int	pipe_to_tab(t_data *data, int i)
{
	t_list	*tab;
	char	*tmp;
	int		j;

	j = 0;
	tmp = malloc(2);
	tab = NULL;
	tmp[j] = '|';
	j++;
	i++;
	tmp[j] = '\0';
	tab = ft_lstnew(tmp, 4);
	ft_lstadd_back(&(data->parse), tab);
	return (i);
}

void	get_content(t_data *data)
{
	char	*line;
	int		i;

	i = 0;
	line = data->readline;
	while (line[i])
	{
		if (line[i] == ' ')
			i++;
		else if (line[i] == '|')
			i = pipe_to_tab(data, i);
		else if (line[i] == '<' || line[i] == '>')
			i = redir_to_tab(data, i);
		else
			i = string_to_tab(data, i);
	}
	expand_parsing(data);
	remove_first_node(data);
	//ft_printlist(data->parse);
}