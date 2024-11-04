#include "../../includes/minishell.h"

void    wait_proc(t_data *data)
{
    int status;
    pid_t pid;
    t_cmd *tmp;

	status = 0;
    tmp = data->cmd;
	signal(SIGINT, SIG_IGN);
    while (tmp != NULL)
    {
        pid = waitpid(0, &status, 0);
        if (pid == g_signal_pid)
        {
            if (WIFEXITED(status))
                data->exit_code = WEXITSTATUS(status);
        }
        if (tmp->infile >= 0)
            close(tmp->infile);
        if (tmp->outfile >= 0)
            close(tmp->outfile);
        tmp = tmp->next;
    }
	signal_childs(status);
	signal(SIGINT, signal_handler);
}

void free_dtab(char **tab)
{
    int i;

    i = 0;
    while (tab[i])
    {
        free (tab[i]);
        i++;
    }
    free (tab);
}

char    *get_envp(char *PATH_NAME, char **envp)
{
    int i;
    int j;
    char *temp;

    i = 0;
    while (envp[i])
    {
        j = 0;
        while (envp[i][j] && envp[i][j] != '=')
            j++;
        temp = ft_substr(envp[i], 0, j);
        if (ft_strncmp(temp, PATH_NAME, 5) == 0)
        {
            free (temp);
            return (envp[i] + j + 1);
        }
        free (temp);
        i++;
    }
    return (NULL);
}

char    *retrieve_path(t_data *data, char *cmd, char **envp)
{
    int i;
    char **dpath;
    char *path_slash;
    char *full_path;

    i = -1;
    data->exit_code = 0;
    dpath = ft_split(get_envp("PATH", envp), ':');
	if (!dpath)
		return (free_dtab(envp), cmd_notfound(data, cmd));
    while (dpath[++i])
    {
        path_slash = ft_strjoin(dpath[i], "/");
        full_path = ft_strjoin(path_slash, cmd);
        free (path_slash);
        if (access(full_path, F_OK) == 0)
        {
            return (full_path);
        }
        free (full_path);
    }
    free_dtab(dpath);
	free_dtab(envp);
    return (cmd_notfound(data, cmd));
}


bool    cmd_exist(char **path, t_data *data, char *cmd)
{
    if (!ft_strchr(cmd, '/'))
        *path = retrieve_path(data, cmd, get_env_refreshed(&(data->env)));
    else
        absolute_path(path, cmd, data);
    if (!(*path))
    {
        data->exit_code = 126;
        return (false);
    }
    if (access((*path), F_OK))
    {
        data->exit_code = 127;
        return (false);
    }
    if (access((*path), R_OK))
    {
        data->exit_code = 126;
        return (false);
    }
    if (access((*path), X_OK))
    {
        data->exit_code = 127;
        return (false);
    }
    return (true);
}