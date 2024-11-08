/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gholloco <gwendal.hollocou@orange.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 05:55:13 by gholloco          #+#    #+#             */
/*   Updated: 2024/11/04 04:04:37 by gholloco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	redir_here_doc(t_data *data, int i)
{
	t_list	*tab;
	char	*tmp;
	int		j;

	while (data->readline[i] && data->readline[i] == ' ')
		i++;
	j = i;
	while (data->readline[j]
		&& data->readline[j] != ' ' && data->readline[j] != '|')
		j++;
	tmp = malloc((j - i + 1) * sizeof(char));
	tab = NULL;
	j = 0;
	while (data->readline[i] && data->readline[i] != ' '
		&& data->readline[i] != '|')
	{
		tmp[j] = data->readline[i];
		j++;
		i++;
	}
	tmp[j] = '\0';
	tab = ft_lstnew(tmp, 9);
	ft_lstadd_back(&(data->parse), tab);
	return (i);
}

int	redir_app_mode(t_data *data, int i)
{
	t_list	*tab;
	char	*tmp;
	int		j;

	while (data->readline[i] && data->readline[i] == ' ')
		i++;
	j = i;
	j = size_of_string(data->readline, j);
	tmp = malloc((j + 1) * sizeof(char));
	tab = NULL;
	ft_strlcpy(tmp, data->readline + i, j + 1);
	tab = ft_lstnew(tmp, 8);
	ft_lstadd_back(&(data->parse), tab);
	i = i + j;
	return (i);
}

int	redir_input(t_data *data, int i)
{
	t_list	*tab;
	char	*tmp;
	int		j;

	while (data->readline[i] && data->readline[i] == ' ')
		i++;
	j = i;
	j = size_of_string(data->readline, j);
	tmp = malloc((j + 1) * sizeof(char));
	tab = NULL;
	ft_strlcpy(tmp, data->readline + i, j + 1);
	tab = ft_lstnew(tmp, 6);
	ft_lstadd_back(&(data->parse), tab);
	i = i + j;
	return (i);
}

int	redir_output(t_data *data, int i)
{
	t_list	*tab;
	char	*tmp;
	int		j;

	while (data->readline[i] && data->readline[i] == ' ')
		i++;
	j = i;
	j = size_of_string(data->readline, j);
	tmp = malloc((j + 1) * sizeof(char));
	tab = NULL;
	ft_strlcpy(tmp, data->readline + i, j + 1);
	tab = ft_lstnew(tmp, 7);
	ft_lstadd_back(&(data->parse), tab);
	i = i + j;
	return (i);
}

int	redir_to_tab(t_data *data, int i)
{
	if (data->readline[i] == '>')
	{
		if (data->readline[i + 1] == '>')
			i = redir_app_mode(data, i + 2);
		else
			i = redir_output(data, i + 1);
	}
	if (data->readline[i] == '<')
	{
		if (data->readline[i + 1] == '<')
			i = redir_here_doc(data, i + 2);
		else
			i = redir_input(data, i + 1);
	}
	return (i);
}
