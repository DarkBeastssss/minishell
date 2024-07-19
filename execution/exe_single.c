/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_single.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebuber <bebuber@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 20:24:41 by bebuber           #+#    #+#             */
/*   Updated: 2024/07/17 18:03:32 by bebuber          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	single_command(t_commend *com, t_list *envl)
{
	int		status;
	char	*path;

	status = 0;
	path = NULL;
	if (com->args[0] == NULL)
		return (0);
	if (ft_strchr(com->args[0], '/'))
	{
		if (access(com->args[0], F_OK) == 0)
			path = ft_strdup(com->args[0]);
	}
	else
		path = find_path(com->args[0], envl);
	if (path == NULL)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(com->args[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		return (127);
	}
	status = execve(path, com->args, NULL);
	free(path);
	return (status);
}
