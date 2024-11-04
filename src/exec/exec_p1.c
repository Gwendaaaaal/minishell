/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_p1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gholloco <gwendal.hollocou@orange.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 06:04:07 by gholloco          #+#    #+#             */
/*   Updated: 2024/11/04 02:27:47 by gholloco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void    redirect_in_out(t_cmd *tmp, int *pid)
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
}

void    child_process(t_data *data, t_cmd *tmp, int *pid)
{
	char *path;
	char **env;

	path = NULL;
	// signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	// signal(SIGQUIT, signal_handler);
	if (is_builtin(tmp->args[0]))
		fd_builtins(data, tmp, pid);
	else if (cmd_exist(&path, data, tmp->args[0]))
	{
		redirect_in_out(tmp, pid);
		env = data->env_char;
		if (!env)
			free_all(data, "error malloc\n", 1);
		execve(path, tmp->args, env);
	}
	if (path)
		free(path);
	free_all(data, NULL, data->exit_code);
}

void    parent_process(t_cmd *tmp, int *pid)
{
    close (pid[1]);
    if (tmp->infile >= 0)
        close (tmp->infile);
    if (tmp->infile == -2)
        tmp->infile = pid[0];
    if (tmp->next && tmp->next->infile == -2)
        tmp->next->infile = pid[0];
    else
        close (pid[0]);
}

void    exec_current(t_data *data, t_cmd *tmp, int *pid)
{
	if (tmp->args && tmp->args[0] && !ft_strncmp("exit", tmp->args[0], 5))
		ft_exit(data, tmp->args + 1);
	else if (tmp->args && tmp->args[0] && !ft_strncmp("cd", tmp->args[0], 3))
		return (data->exit_code = ft_cd(&(data->env), tmp->args + 1), close_both_pid(pid[0], pid[1]));
	else if (tmp->args && tmp->args[0] && !ft_strncmp("export", tmp->args[0], 7))
		return (data->exit_code = ft_export(&(data->env), tmp->args + 1, data->exit_code), close_both_pid(pid[0], pid[1]));
	else if (tmp->args && tmp->args[0] && !ft_strncmp("unset", tmp->args[0], 6))
		return (data->exit_code = ft_unset(&(data->env), tmp->args + 1), close_both_pid(pid[0], pid[1]));
	g_signal_pid = fork();
	if (g_signal_pid < 0)
		free_all(data, "fork error\n", 1);
	else if (!g_signal_pid)
	{
		if (tmp->args && tmp->args[0])
			child_process(data, tmp, pid);
		else
			free_all(data, NULL, 0);
	}
	else
		parent_process(tmp, pid);
}

void    exec_cmd(t_data *data)
{
    t_cmd *tmp;
    int *pid;

    pid = data->pid;
    tmp = data->cmd;
    if (pipe(pid) == -1)
       return ;
    while (tmp != NULL && (tmp->infile == -1 || tmp->outfile == -1))
    {
        if (tmp->next && tmp->next->infile < 0 && (!ft_strncmp(tmp->args[0], "cat", 4) && !ft_strncmp(tmp->next->args[0], "cat", 4)))
        {
            data->exit_code = 0;
            tmp = tmp->next;
        }
        tmp = tmp->next;
    }
    if (tmp)
    {
        exec_current(data, tmp, pid);
        tmp = tmp->next;
    }
    while (tmp != NULL)
    {
        if (pipe(pid) == -1)
            return ;
        if (tmp->infile != -1 && tmp->outfile != -1)
            exec_current(data, tmp, pid);
        tmp = tmp->next;
    }
    wait_proc(data);
	ft_free_cmd(data);
}
