/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gholloco <gwendal.hollocou@orange.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 00:03:54 by gholloco          #+#    #+#             */
/*   Updated: 2024/11/04 00:59:53 by gholloco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	cd(t_env **env, char *dir)
{
	char	cwd[PATH_MAX];
	int		need_free;
	int		ret;

	need_free = 0;
	if (!dir || !ft_strncmp(dir, "~", 2))
	{
		dir = get_env_variable(env, "HOME");
		need_free = 1;
	}
	if (!ft_strncmp(dir, "-", 2))
	{
		dir = get_env_variable(env, "OLDPWD");
		printf("%s\n", dir);
		need_free = 1;
	}
	getcwd(cwd, PATH_MAX);
	ret = chdir(dir);
	if (!ret)
	{
		known_export(env, "OLDPWD", cwd);
		getcwd(cwd, PATH_MAX);
		known_export(env, "PWD", cwd);
	}
	if (need_free)
		free(dir);
	return (ret);
}

int	ft_cd(t_env **env, char **dir)
{
	int i;
	int ret;

	i = 0;
	while(dir[i])
		i++;
	if (i >= 2)
		return(write(2, "-minishell: cd: too many arguments\n", 35), 1);
	ret = cd(env, dir[0]);
	if (ret == -1)
		return (write(2, "-minishell: cd: No such file or directory\n", 42), 1);
	return (ret);
}
// int	main(int argc, char **argv)
// {
// 	t_data	*data;
//
// 	data = init_data();
// 	cd(&(data->env), argv[1]);
// 	env(&(data->env));
// 	cd(&(data->env), argv[2]);
// 	env(&(data->env));
// 	free_env(&(data->env));
// 	free(data);
// 	return (0);
// }
