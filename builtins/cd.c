/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebuber <bebuber@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 15:41:01 by bebuber           #+#    #+#             */
/*   Updated: 2024/07/23 10:20:17 by bebuber          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
// #include "mini.h"

char	*get_env_value(char *key, char **env)
{
	int		i;
	int		j;
	char	*value;

	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j] && env[i][j] != '=')
			j++;
		if (strncmp(env[i], key, j) == 0)
		{
			value = ft_strdup(env[i] + j + 1);
			if (!value)
				return (NULL);
			return (value);
		}
		i++;
	}
	return (NULL);
}

int	set_address(char ***env)
{
	char	*oldpwd;
	char	*pwd;

	oldpwd = get_env_value("PWD", (*env));
	pwd = getcwd(NULL, 0);
	update_env("OLDPWD=", oldpwd, env);
	update_env("PWD=", pwd, env);
	free(pwd);
	return (0);
}

int	cd(char **args, char **env)
{
	char	*path;

	if (!args[1] || strcmp(args[1], "~") == 0)
		path = get_env_value("HOME", env);
	else if (args[1][0] == '$' && args[1][1] != '\0')
	{
		path = get_env_value(args[1] + 1, env);
		if (!path || chdir(path) == -1)
			path = get_env_value("HOME", env);
	}
	else
		path = args[1];
	if (chdir(path) == -1)
	{
		print_error("cd", path, "No such file or directory");
		return (1);
	}
	else
		set_address(&env);
	return (0);
}
