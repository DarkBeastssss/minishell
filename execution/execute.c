/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebuber <bebuber@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 19:20:41 by bebuber           #+#    #+#             */
/*   Updated: 2024/07/17 21:19:37 by bebuber          ###   ########.fr       */
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

int	ft_strcmp(const char *s1, const char *s2)
{
	int				i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

int	builtin_commands(char **args, t_data *data)
{
	char	*command;
	int		result;

	result = 0;
	command = args[0];
	if (!ft_strcmp(command, "cd"))
		result = ft_cd(args, data->env);
	else if (!ft_strcmp(command, "echo"))
		result = ft_echo(args);
	else if (!ft_strcmp(command, "pwd"))
		result = ft_pwd();
	else if (!ft_strcmp(command, "export"))
		result = ft_export(args, &data->env);
	else if (!ft_strcmp(command, "unset"))
		result = ft_unset(args, &data->env);
	else if (!ft_strcmp(command, "env"))
		result = ft_env(data->env);
	else if (!ft_strcmp(command, "exit"))
		result = ft_exit(data);
	return (result);
}

void	execute(t_data *mini)
{
	if (count_commands(mini->cmmds) == 1)
	{
		execute_single_command(mini);
	}
	else
	{
		execute_multiple_commands(mini);
	}
}
