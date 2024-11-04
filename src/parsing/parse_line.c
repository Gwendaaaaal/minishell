/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gholloco <gwendal.hollocou@orange.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 05:51:50 by gholloco          #+#    #+#             */
/*   Updated: 2024/10/27 05:52:54 by gholloco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_syntax(char *line)
{
	int	i;
	int	quote;
	int	pipe;

	i = 0;
	quote = 0;
	pipe = 0;
	while (line[i])
	{
		if (line[i] == '|' && quote == 0 && pipe == 1)
			return (0);
		if (line [i] == '|' && quote == 0 && pipe == 0)
			pipe = 1;
		else if (line[i] != '|' && line[i] != ' ')
			pipe = 0;
		if ((line[i] == '\'' || line[i] == '\"') && quote == 0)
			quote = 1;
		else if ((line[i] == '\'' || line[i] == '\"') && quote == 1)
			quote = 0;
		i++;
	}
	return (1);
}

int	check_quotes(char *line)
{
	int	i;
	int	quote;
	int	dquote;

	i = 0;
	quote = 0;
	dquote = 0;
	if (!line)
		return (1);
	while (line[i])
	{
		if (line[i] == '\'' && quote == 0 && dquote == 0)
			quote = 1;
		else if (line[i] == '\"' && quote == 0 && dquote == 0)
			dquote = 1;
		else if (line[i] == '\'' && quote == 1)
			quote = 0;
		else if (line[i] == '\"' && dquote == 1)
			dquote = 0;
		i++;
	}
	if (quote == 1 || dquote == 1)
		return (0);
	return (1);
}
