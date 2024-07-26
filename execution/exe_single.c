/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_single.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebuber <bebuber@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 20:24:41 by bebuber           #+#    #+#             */
/*   Updated: 2024/07/26 17:33:16 by bebuber          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*find_path(char **env, char *command)
{
	char	*path;
	char	**paths;
	char	*all_paths;
	int		i;

	i = 0;
	all_paths = get_env_value("PATH", env);
	if (!all_paths)
	{
		print_error("minishell", command, "No such file or directory");
		return (data->exit_code = 127, NULL);
	}
	paths = ft_split(all_paths, ':');
	free(all_paths);
	while (paths[i])
	{
		path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(path, command);
		if (access(path, X_OK) == 0)
			return (free_arr(paths), path);
		free(path);
		i++;
	}
	print_error("minishell", command, "Command not found");
	return (free_arr(paths), NULL);
}

void	close_fds(int *fd)
{
	close(fd[0]);
	close(fd[1]);
}

void	fork_the_command(t_data *data, pid_t *pid)
{
	*pid = fork();
	if (*pid == 0)
	{
		if (execve(find_path(data->env, data->cmmds->args[0]), \
		data->cmmds->args, data->env) == -1)
		{
			data->exit_code = 127;
			exit(127);
		}
	}
	else if (*pid < 0)
	{
		ft_putstr_fd("minishell: fork failed", 2);
		data->exit_code = 1;
	}
}

int	execute_single_command(t_data *data)
{
	int		status;
	int		fd[2];
	pid_t	pid;

	fd[0] = dup(0);
	fd[1] = dup(1);
	if (data->cmmds->fd_in != -1)
	{
		dup2(data->cmmds->fd_in, 0);
		close(data->cmmds->fd_in);
	}
	if (data->cmmds->fd_out != -1)
	{
		dup2(data->cmmds->fd_out, 1);
		close(data->cmmds->fd_out);
	}
	fork_the_command(data, &pid);
	waitpid(pid, &status, 0);
	dup2(fd[0], 0);
	dup2(fd[1], 1);
	close_fds(fd);
	if (WIFEXITED(status))
		data->exit_code = WEXITSTATUS(status);
	return (0);
}
