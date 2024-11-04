/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gholloco <gwendal.hollocou@orange.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 19:57:07 by gholloco          #+#    #+#             */
/*   Updated: 2024/11/03 08:56:10 by gholloco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	check_number(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
		if (!ft_isdigit(str[i++]))
			return (0);
	return (1);
}

static int	check_long_long(char *num)
{
	int	num_len;

	if (!check_number(num))
		return (0);
	num_len = ft_strlen(num);
	if (num_len > 19) 	
	{
		if (num[0] == '-')
		{
			if (num_len == 20 && ft_strncmp(num, "-9223372036854775808", 20) > 0)
				return (0);
		}
		else if (num[0] == '+')
		{
			if (num_len == 20 && ft_strncmp(num, "+9223372036854775807", 20) > 0)
				return (0);
		}
		else
			return (0);
	}
	if (ft_strncmp(num, "9223372036854775807", 20) > 0)
		return (0);
	return (1);
}

long long	ft_atoll(const char *nptr)
{
	int			i;
	int			minus;
	long long	res;

	i = 0;
	res = 0;
	minus = 1;
	while (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			minus *= -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		res = (res * 10) + (nptr[i] - 48);
		i++;
	}
	return (res * minus);
}

void	ft_exit(t_data *data, char **args)
{
	int	exit_code;

	exit_code = g_signal_pid;
	if (args[0])
	{
		if (check_number(args[0]) && check_long_long(args[0]))
			exit_code = ft_atoll(args[0]) % 256; 
		else
		{
			write(2, "minishell : exit : numeric argument required\n", 45);
			free_all(data, "exit", 2);
		}
		if (args[1])
		{
			write(2, "minishell : exit : too many arguments\n", 38);
			free_all(data, "exit", 1);
			return ;
		}
	}
	free_all(data, "exit", exit_code);
}
