/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebuber <bebuber@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 18:35:25 by bebuber           #+#    #+#             */
/*   Updated: 2024/07/19 16:18:15 by bebuber          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	printexport(char **env)
{
	int		i;
	int		j;

	j = 0;
	i = 0;
	while (env[i])
	{
		ft_putstr_fd("declare -x ", 1);
		while (env[i][j] && env[i][j] != '=')
			ft_putchar_fd(env[i][j++], 1);
		if (env[i][j] == '=')
		{
			ft_putstr_fd('="', 1);
			ft_putstr_fd(env[i] + j + 1, 1);
			ft_putchar_fd('"', 1);
		}
		ft_putchar_fd('\n', 1);
		i++;
	}
}

int	export(char **env, char **args)
{
	int		i;
	int		ret;

	i = 1;
	ret = 0;
	if (!args[i])
		printexport(env);
	else
	{
		while (args[i])
		{
			ret = add_new_env(args[i], "", &env);
			i++;
		}
	}
	return (ret);
}
