/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_multiple.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebuber <bebuber@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 17:56:23 by bebuber           #+#    #+#             */
/*   Updated: 2024/07/26 23:39:35 by bebuber          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	allocate_pipes(int ***fd, pid_t **pid, int nb_cmmds)
{
	int	i;

	*fd = malloc(sizeof(int *) * nb_cmmds);
	if (!*fd)
		return (ft_putstr_fd("minishell: malloc failed", 2), 1);
	*pid = malloc(sizeof(pid_t) * nb_cmmds);
	if (!*pid)
		return (free (*fd), ft_putstr_fd("minishell: malloc failed", 2), 1);
	i = -1;
	while (++i < nb_cmmds)
	{
		(*fd)[i] = malloc(sizeof(int) * 2);
		if (!(*fd)[i])
		{
			while (i >= 0)
				free((*fd)[i--]);
			free(*fd);
			free(*pid);
			return (ft_putstr_fd("minishell: malloc failed", 2), 1);
		}
		pipe((*fd)[i]);
	}
	return (0);
}

int	wait_all_children(pid_t *pid, t_data *data, int nb_cmds)
{
	int	i;
	int	status;

	i = -1;
	while (++i < nb_cmds)
	{
		if (waitpid(pid[i], &status, 0) == -1)
		{
			ft_putendl_fd("minishell: waitpid error", 2);
			data->exit_code = 1;
			return (1);
		}
		if (WIFEXITED(status))
			data->exit_code = WEXITSTATUS(status);
	}
	return (0);
}

void	adjust_pipes_and_fds(int **fd, int i, int nb_cmds, t_command *cmds)
{
	if (i == 0)
		dup2(fd[i][1], 1);
	else if (i == nb_cmds - 1)
		dup2(fd[i - 1][0], 0);
	else
	{
		dup2(fd[i - 1][0], 0);
		dup2(fd[i][1], 1);
	}
	if (cmds->fd_in != -1)
		dup2(cmds->fd_in, 0);
	if (cmds->fd_out != -1)
		dup2(cmds->fd_out, 1);
	close(cmds->fd_in);
	close(cmds->fd_out);
	close_all_pipes(fd, nb_cmds);
}

void	fork_all_children(t_data *data, t_command *cmds, int i)
{
	data->pid[i] = fork();
	if (data->pid[i] == 0)
	{
		adjust_pipes_and_fds(data->fd, i, count_commands(data->cmmds), cmds);
		if (builtin_commands(cmds->args, data) == 0)
			exit(0);
		if (execve(find_path(data->env, cmds->args[0], data), \
		cmds->args, data->env) == -1)
			exit((data->exit_code = 127));
	}
	else if (data->pid[i] < 0)
	{
		ft_putendl_fd("minishell: fork failed", 2);
		data->exit_code = 1;
	}
}

int	execute_multiple_commands(t_data *data)
{
	int			nb_cmds;
	t_command	*cmds;
	int			i;

	i = -1;
	cmds = data->cmmds;
	nb_cmds = count_commands(data->cmmds);
	if (allocate_pipes(&data->fd, &data->pid, nb_cmds))
		return (data->exit_code = 1, 1);
	while (cmds)
	{
		fork_all_children(data, cmds, ++i);
		cmds = cmds->next;
	}
	close_all_pipes(data->fd, nb_cmds);
	wait_all_children(data->pid, data, nb_cmds);
	free_all_pipes(data->fd, data->pid, nb_cmds);
	return (0);
}
