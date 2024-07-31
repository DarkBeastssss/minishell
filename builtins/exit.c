/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebuber <bebuber@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 18:35:05 by bebuber           #+#    #+#             */
/*   Updated: 2024/07/31 16:07:22 by bebuber          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_error(char *command, char *arg, char *error)
{
	ft_putstr_fd(command, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(error, 2);
}

int	ft_exit(char **args, t_data *data)
{
	int		i;

	i = 0;
	if (args[1])
	{
		if (args[2])
		{
			print_error("exit", args[1], "too many arguments");
			return (1);
		}
		while (args[1][i])
		{
			if (i == 0 && args[1][i] == '-')
				i++;
			if (!ft_isdigit(args[1][i]))
			{
				print_error("exit", args[1], "numeric argument required");
				(data->exit_code = 255);
				exit(255);
			}
			i++;
		}
		data->exit_code = (ft_atoi(args[1]) % 256);
	}
	system("leaks minishell");
	free_arr(data->env);
	exit(data->exit_code);
}
