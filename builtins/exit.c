/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebuber <bebuber@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 18:35:05 by bebuber           #+#    #+#             */
/*   Updated: 2024/07/26 17:28:14 by bebuber          ###   ########.fr       */
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

int	ft_exit(t_command *cmmds, t_data *data)
{
	int		i;

	i = 0;
	if (cmmds->args[1])
	{
		if (cmmds->args[2])
		{
			print_error("exit", cmmds->args[1], "too many arguments");
			return (1);
		}
		while (cmmds->args[1][i])
		{
			if (i == 0 && cmmds->args[1][i] == '-')
				i++;
			if (!ft_isdigit(cmmds->args[1][i]))
			{
				print_error("exit", \
				cmmds->args[1], "numeric argument required");
				exit((data->exit_code = 255), 255);
			}
			i++;
		}
		data->exit_code = (ft_atoi(cmmds->args[1]) % 256);
	}
	exit(data->exit_code);
}
