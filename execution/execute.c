/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebuber <bebuber@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 19:20:41 by bebuber           #+#    #+#             */
/*   Updated: 2024/07/23 10:30:10 by bebuber          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_commands(t_command *current)
{
	int		count;

	count = 0;
	while (current)
	{
		count++;
		current = current->next;
	}
	return (count);
}

int	builtin_commands(char **args, t_data *data)
{
	char	*command;
	int		err_stat;

	err_stat = -1;
	command = args[0];
	if (!ft_strcmp(command, "cd"))
		err_stat = cd(args, data->env);
	else if (!ft_strcmp(command, "echo"))
		err_stat = echo(args);
	else if (!ft_strcmp(command, "pwd"))
		err_stat = pwd(args);
	else if (!ft_strcmp(command, "export"))
		err_stat = export(args, &data->env);
	else if (!ft_strcmp(command, "unset"))
		err_stat = unset(args, &data->env);
	else if (!ft_strcmp(command, "env"))
		err_stat = env(data->env, args);
	else if (!ft_strcmp(command, "exit"))
		err_stat = ft_exit(args, data);
	else
		return (1);
	if (err_stat != -1)
		data->exit_code = err_stat;
	return (0);
}

void	execute(t_data *data)
{
	alloc_env(&data->env);
	if (count_commands(data->cmmds) == 1)
		execute_single_command(data);
	else
		execute_multiple_commands(data);
}
