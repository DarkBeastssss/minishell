/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebuber <bebuber@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 19:20:41 by bebuber           #+#    #+#             */
/*   Updated: 2024/07/31 21:04:28 by bebuber          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	alloc_env(char ***env, char **environ)
{
	int			i;
	int			len;

	i = 0;
	while (environ[i])
		i++;
	*env = (char **)malloc(sizeof(char *) * (i + 1));
	len = 0;
	i = 0;
	while (environ[i])
	{
		len = ft_strlen(environ[i]);
		(*env)[i] = (char *)malloc(sizeof(char) * (len + 1));
		if (!(*env)[i])
		{
			while (i >= 0)
				free((*env)[i--]);
			free(*env);
			return (ft_putendl_fd("Memory allocation failed", 2), 1);
		}
		ft_strlcpy((*env)[i], environ[i], len + 1);
		i++;
	}
	return ((*env)[i] = NULL, 0);
}

int	builtin_commands(char **args, t_data *data)
{
	char	*command;
	int		err_stat;

	err_stat = -1;
	command = args[0];
	if (!ft_strcmp(command, "cd"))
		err_stat = cd(args, &data->env);
	else if (!ft_strcmp(command, "echo"))
		err_stat = echo(args);
	else if (!ft_strcmp(command, "pwd"))
		err_stat = pwd(args);
	else if (!ft_strcmp(command, "export"))
		err_stat = export(args, &data->env);
	else if (!ft_strcmp(command, "unset"))
		err_stat = unset(&data->env, args);
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
	signal_handler(EXECUTION);
	if (count_commands(data->cmmds) == 1)
		execute_single_command(data);
	else
		execute_multiple_commands(data);
}
