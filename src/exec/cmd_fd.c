#include "../../includes/minishell.h"

void	open_input(t_data *data, t_cmd *cmd, char *content)
{
	if (cmd->infile >= 0)
		close (cmd->infile);
	if (cmd->infile == -1)
		return;
	cmd->infile = open(content, O_RDONLY, 0644);
	if (cmd->infile == -1)
		data->exit_code = 1;
}

void	open_output(t_data *data, t_cmd *cmd, char *content)
{
	if (cmd->outfile >= 0)
		close (cmd->outfile);
	if (cmd->outfile == -1)
		return;
	cmd->outfile = open(content, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (cmd->outfile == -1)
		data->exit_code = 1;
}

void	open_append(t_data *data, t_cmd *cmd, char *content)
{
	if (cmd->outfile >= 0)
		close (cmd->outfile);
	if (cmd->outfile == -1)
		return;
	cmd->outfile = open(content, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (cmd->outfile == -1)
		data->exit_code = 1;
}

void	change_fd(t_data *data, t_cmd *cmd, int token, char *content)
{
	if (token == 6)
		open_input(data, cmd, content);
	if (token == 7)
		open_output(data, cmd, content);
	if (token == 8)
		open_append(data, cmd, content);
	if (token == 9)
		open_here(data, cmd, content);
}

void	fd_to_tab(t_data *data)
{
	t_list	*tmp;
	t_cmd	*tcmd;

	tmp = data->parse;
	tcmd = data->cmd;
	while (tmp != NULL)
	{
		while (tmp != NULL)
		{
			if (tmp->token > 5)
				change_fd(data, tcmd, tmp->token, tmp->content);
			if (tmp->token != 4)
				tmp = tmp->next;
			else
				break ;
		}
		if (tmp != NULL && tmp->token == 4)
		{
			tcmd = tcmd->next;
			tmp = tmp->next;
		}
	}
}
