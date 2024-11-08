/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gholloco <gwendal.hollocou@orange.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 12:41:38 by gholloco          #+#    #+#             */
/*   Updated: 2024/11/08 02:40:58 by gholloco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// includes
# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <signal.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <fcntl.h>
# include "Libft/libft.h"
# include <stdbool.h>
# include <sys/wait.h>
# include <sys/stat.h>

extern pid_t	g_signal_pid;

typedef struct s_env
{
	char			*variable;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_cmd
{
	char			**args;
	int				outfile;
	int				infile;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_data
{
	char	*prompt;
	char	*readline;
	char	**env_char;
	t_env	*env;
	t_list	*parse;
	t_cmd	*cmd;
	int		pid[2];
	int		exit_code;
}	t_data;

t_data	*init_data(char **envp);

//parsing.c
int		check_quotes(char *line);
int		check_syntax(char *line);
void	get_content(t_data *data);
int		redir_to_tab(t_data *data, int i);
int		size_of_string(char *str, int j);

//expand.c
char	*expand(t_data *data, char *string, int heredoc);
int		expand_parsing(t_data *data);

//tools.c
char	**split_in_two(char const *s, char c);
void	error_exit(char *msg);
void	ft_printlist(t_list *tab);
void	ft_print_tab(t_cmd *cmd);
void	ft_cmdadd_back(t_cmd **lst, t_cmd *new);
void	open_here(t_data *data, t_cmd *cmd, char *word);
void	ft_freelist(t_list *tab);
void	free_all(t_data *data, char *error, int ext);
char	**get_env_refreshed(t_env **env);
void	ft_free_cmd(t_data *data);
int		last_pipe(t_list *parse);
void	close_both_pid(int pid1, int pid2);
void	ft_print_list_no_free(t_env **env);
t_env	*add_back_env(t_env **env, char *variable, char *value);
void	skip_cmd(t_cmd **tmp, t_data *data);

//		str_utils.c
char	*ft_strjoin_with_free(char *s1, char const *s2);
char	*ft_strjoin_with_double_free(char *s1, char *s2);
char	*ft_strappend(char *string, char c);

//exec.c
void	make_cmd(t_data *data);
void	list_to_tab(t_list *parse, t_cmd *cmd);
void	fd_to_tab(t_data *data);
void	exec_cmd(t_data *data);
bool	cmd_exist(char **path, t_data *data, char *tmp);
void	wait_proc(t_data *data);
void	absolute_path(char **path, char *cmd, t_data *data);
void	check_dir(char **path, char *cmd, t_data *data);
char	*cmd_notfound(t_data *data, char *cmd);
bool	is_builtin(char *cmd);
void	fd_builtins(t_data *data, t_cmd *tmp, int *pid);
void	exec_builtin(t_data *data, t_cmd *tmp);
void	launch_builtin(t_data *data, t_cmd *tmp);

//signals.c
int		init_signals(void);
void	signal_handler(int sig);
void	signal_pid(void);
void	signal_childs(int sig);
void	signal_heredoc(int sig);

//builtins
// pwd.c
int		ft_pwd(void);

//echo.c
int		ft_echo(char **args);

// env.c
void	free_env_node(t_env *node);
void	free_env(t_env **env);
char	*get_env_variable(t_env **env, char *variable);
int		get_env_length(t_env **env);
int		ft_env(t_env **env);

// export.c
int		known_export(t_env **env, char *variable, char *value);
int		ft_export(t_env **env, char **line, int old_exit_code);
int		export(t_env **env, char *line);

// unset.c
int		ft_unset(t_env **env, char **variable);

// cd.c
int		ft_cd(t_env **env, char **dir);

// exit.c
void	ft_exit(t_data *data, char **args);

#endif
