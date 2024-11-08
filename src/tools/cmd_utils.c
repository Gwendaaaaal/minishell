/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gholloco <gwendal.hollocou@orange.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 02:57:53 by gholloco          #+#    #+#             */
/*   Updated: 2024/11/08 14:58:27 by gholloco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdlib.h>
#include <unistd.h>

void	unlink_close(char *name, int fd)
{
	unlink(name);
	close(fd);
}

void	get_doc(t_data *data, int fd, char *word)
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
	ft_free_cmd(data);
	ft_freelist(data->parse);
	free_env(&(data->env));
	free(data->readline);
	free(data);
}

void	open_here(t_data *data, t_cmd *cmd, char *word)
{
	int	fd;
	int	pid;
	int	status;	

	fd = open(".heredoc.tmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (cmd->infile != -2)
		close(cmd->infile);
	if (fd < 0)
		cmd->infile = -1;
	pid = fork();
	if (pid == -1)
		return unlink_close(".heredoc.tmp", fd);
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		get_doc(data, fd, word);
		exit(0);
	}
	close(fd);
	signal(SIGINT, SIG_IGN);
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		printf("\n");
		cmd->infile = -1;
		return (data->exit_code = 130, unlink_close(".heredoc.tmp", fd));
	}
	fd = open(".heredoc.tmp", O_RDONLY);
	if (fd > 0)
		unlink(".heredoc.tmp");
	cmd->infile = fd;
}
