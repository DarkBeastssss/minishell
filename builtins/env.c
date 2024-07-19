/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebuber <bebuber@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 18:34:57 by bebuber           #+#    #+#             */
/*   Updated: 2024/07/19 12:51:02 by bebuber          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	env(char **env, char **args)
{
	int		i;

	i = 1;
	while (args[i])
	{
		if (i > 1)
		{
			print_error("env", args[i], "No such file or directory");
			return (1);
		}
		i++;
	}
	i = 0;
	while (env[i])
	{
		ft_putendl_fd(env[i], 1);
		i++;
	}
	return (0);
}

