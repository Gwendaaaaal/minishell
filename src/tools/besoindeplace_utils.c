/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   besoindeplace_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gholloco <gwendal.hollocou@orange.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 23:02:05 by gholloco          #+#    #+#             */
/*   Updated: 2024/11/03 23:03:06 by gholloco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	close_both_pid(int pid1, int pid2)
{
	close(pid1);
	close(pid2);
	return ;
}

void	check_dir(char **path, char *cmd, t_data *data)
{
	struct stat	path_stat;

	stat(*path, &path_stat);
	if (!S_ISREG(path_stat.st_mode))
	{
		write(2, cmd, ft_strlen(cmd));
		write(2, " : Is a directory\n", 18);
		data->exit_code = 126;
		free_all(data, NULL, data->exit_code);
	}
	return ;
}