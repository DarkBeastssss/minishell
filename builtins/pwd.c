/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebuber <bebuber@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 15:25:45 by bebuber           #+#    #+#             */
/*   Updated: 2024/07/19 11:04:50 by bebuber          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	pwd(char **args)
{
	char	*cwd;

	(void)args;
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (1);
	ft_putendl_fd(cwd, 1);
	free(cwd);
	return (0);
}
