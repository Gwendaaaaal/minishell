#include "../../includes/minishell.h"

void	launch_builtin(t_data *data, t_cmd *tmp)
{
	int	save_stdout;

	save_stdout = -1;
	if (tmp->outfile >= 0)
	{
		save_stdout = dup(1);
		dup2(tmp->outfile, 1);
	}
	exec_builtin(data, tmp);
	if (tmp->outfile >= 0)
	{
		dup2(save_stdout, 1);
		close (save_stdout);
	}
}

void	fd_builtins(t_data *data, t_cmd *tmp, int *pid)
{
    close(pid[0]);
    if (tmp->infile >= 0)
    {
        dup2(tmp->infile , 0);
        close (tmp->infile);
    }
    if (tmp->outfile >= 0)
    {
        dup2(tmp->outfile, 1);
        close (tmp->outfile);
    }
    else if (tmp->next)
        dup2(pid[1], 1);
    close(pid[1]);
	launch_builtin(data, tmp);
}

bool	is_builtin(char *cmd)
{
	if (!cmd)
		return (false);
	if (!ft_strncmp("echo", cmd, 5) || !ft_strncmp("cd", cmd, 3) \
	|| !ft_strncmp("pwd", cmd, 4) || !ft_strncmp("export", cmd, 7) \
	|| !ft_strncmp("unset", cmd, 6) || !ft_strncmp("env", cmd, 4) \
	|| !ft_strncmp("exit", cmd, 5))
		return (true);
	return (false);
}

void	absolute_path(char **path, char *cmd, t_data *data)
{
	*path = ft_strdup(cmd);
	if (access((*path), X_OK))
            data->exit_code = 127;
	else if (access((*path), F_OK))
	{
		write(2, (*path), ft_strlen((*path)));
		write(2, " : command not found\n", 21);
		data->exit_code = 127;
	}
	else
		check_dir(path, cmd, data);
}

char    *cmd_notfound(t_data *data, char *cmd)
{
    write(2, cmd, ft_strlen(cmd));
	write(2, " : command not found\n", 21);
	data->exit_code = 127;
	free_all(data, NULL, data->exit_code);
	return (NULL);
}
