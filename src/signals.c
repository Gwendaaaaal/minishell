/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gholloco <gwendal.hollocou@orange.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 15:05:01 by gholloco          #+#    #+#             */
/*   Updated: 2024/11/01 00:06:13 by gholloco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <readline/readline.h>
#include <signal.h>

void	signal_childs(int sig)
{
	if (WIFSIGNALED(sig))
	{
		if (WTERMSIG(sig) == SIGINT)
			write(1, "\n", 1);
		else if (WTERMSIG(sig) == SIGQUIT)
			printf("Quit (core dumped)\n");
		return ;
	}
}

void	signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		g_signal_pid = 130;
	}
}

int	init_signals(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
	return (0);
}
