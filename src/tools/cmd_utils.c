/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gholloco <gwendal.hollocou@orange.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 02:57:53 by gholloco          #+#    #+#             */
/*   Updated: 2024/11/04 01:58:56 by gholloco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	get_doc(t_data *data, int fd, char *word)
{
	char	*buf;
	char	*tmp;

	while (1)
	{
		buf = NULL;
		buf = readline("> ");
		if (!buf || !ft_strncmp(word, buf, INT_MAX))
			break ;

		tmp = expand(data, buf, 1);
		free(buf);
		buf = tmp;
		write(fd, buf, ft_strlen(buf));
		write(fd, "\n", 1);
		free (buf);
	}
	free(buf);
	close(fd);
	return (true);
}

void	open_here(t_data *data, t_cmd *cmd, char *word)
{
	int	fd;

	fd = open(".heredoc.tmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		cmd->infile = -1;
	if (!get_doc(data, fd, word))
	{
		unlink(".heredoc.tmp");
		cmd->infile = -1;
	}
	fd = open(".heredoc.tmp", O_RDONLY);
	if (fd > 0)
		unlink(".heredoc.tmp");

	// a delete un jour
	// char *buff;
	// while (read(fd, buff, 10000))
	// {
	// 	printf("%s\n", buff);
	// }

	cmd->infile = fd;
}
