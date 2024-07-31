/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amecani <amecani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 18:35:25 by bebuber           #+#    #+#             */
/*   Updated: 2024/07/31 17:07:45 by amecani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	printexport(char **env)
{
	int		i;
	int		j;

	j = 0;
	i = 0;
	while (env[i])
	{
		j = 0;
		ft_putstr_fd("declare -x ", 1);
		while (env[i][j] && env[i][j] != '=')
			ft_putchar_fd(env[i][j++], 1);
		if (env[i][j] == '=')
		{
			ft_putchar_fd('=', 1);
			ft_putchar_fd('"', 1);
			ft_putstr_fd(env[i] + j + 1, 1);
			ft_putchar_fd('"', 1);
		}
		ft_putchar_fd('\n', 1);
		i++;
	}
}

int	check_if_key_exists(char *key, char **env)
{
	int		i;
	int		j;

	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j] && env[i][j] != '=')
			j++;
		if (ft_strncmp(env[i], key, j) == 0)
			return (0);
		i++;
	}
	return (1);
}

void	find_key_value(char *arg, char **key, char **value)
{
	int		i;

	i = 0;
	if (ft_strchr(arg, '='))
	{
		while (arg[i] && arg[i] != '=')
			i++;
		*key = ft_substr(arg, 0, i);
		*value = ft_strdup(arg + i);
	}
	else
	{
		*key = ft_strdup(arg);
		*value = "";
	}
}

int	export(char **args, char ***env)
{
	int		i;
	int		ret;
	char	*key;
	char	*value;

	i = 1;
	ret = 0;
	if (!args[i])
		printexport(*env);
	else
	{
		while (args[i])
		{
			find_key_value(args[i], &key, &value);
			if (check_if_key_exists(key, (*env)))
				ret = add_new_env(key, value, env);
			else if (ft_strchr(args[i], '='))
				ret = update_env(key, value, env);
			free(key);
			if (value[0])
				free(value);
			i++;
		}
	}
	return (ret);
}
