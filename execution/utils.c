/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebuber <bebuber@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 17:26:21 by bebuber           #+#    #+#             */
/*   Updated: 2024/07/26 23:20:40 by bebuber          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	int				i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

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