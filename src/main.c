/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gholloco <gwendal.hollocou@orange.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 03:07:41 by gholloco          #+#    #+#             */
/*   Updated: 2024/11/08 00:55:15 by gholloco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

pid_t	g_signal_pid;

int	check_line(t_data *data)
{
	while (1)
	{
		init_signals();
		data->readline = (readline(data->prompt));
		if (!data->readline)
			return (free (data->readline), free_env(&(data->env)),
				free (data), 1);
		if (!check_quotes(data->readline) || !check_syntax(data->readline))
		{
			free(data->readline);
			data->exit_code = 2;
			write(2, "invalid syntax.\n", 16);
		}
		else
		{
			get_content(data);
			if (data->parse)
				make_cmd(data);
			if (ft_strlen(data->readline) != 0)
				add_history(data->readline);
			free (data->readline);
			data->parse = NULL;
			g_signal_pid = 0;
		}
	}
}

int	main(int ac, char **av, char **envp)
{
	t_data	*data;

	(void) av;
	if (ac != 1)
		error_exit("too many arguments.");
	data = init_data(envp);
	init_signals();
	if (check_line(data) == 1)
		printf("exit\n");
	rl_clear_history();
}
