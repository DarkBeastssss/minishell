/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_multiple.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebuber <bebuber@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 17:56:23 by bebuber           #+#    #+#             */
/*   Updated: 2024/07/26 21:15:37 by bebuber          ###   ########.fr       */
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

void	close_all_pipes(int **fd, int nb_cmds)
{
	int	i;

	i = -1;
	while (++i < nb_cmds)
	{
		close(fd[i][0]);
		close(fd[i][1]);
	}
}

void	free_all_pipes(int **fd, pid_t *pid, int nb_cmds)
{
	int	i;

	i = -1;
	while (++i < nb_cmds)
		free(fd[i]);
	free(fd);
	free(pid);
}

int_least64_t	wait_all_children(pid_t *pid, t_data *data, int nb_cmds)
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

int	execute_multiple_commands(t_data *data)
{
	int			**fd;
	pid_t		*pid;
	int			nb_cmds;
	t_command	*cmds;
	int			i;

	i = -1;
	cmds = data->cmmds;
	nb_cmds = count_commands(data->cmmds);
	if (allocate_pipes(&fd, &pid, nb_cmds))
		return (data->exit_code = 1, 1);
	while (cmds)
	{
		fork_all_children(data, pid, fd, ++i);
		cmds = cmds->next;
	}
	close_all_pipes(fd, nb_cmds);
	wait_all_children(pid, data, nb_cmds);
	free_all_pipes(fd, pid, nb_cmds);
	return (0);
}
