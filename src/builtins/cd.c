/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amecani <amecani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 15:41:01 by bebuber           #+#    #+#             */
/*   Updated: 2024/07/31 22:26:57 by amecani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	char	*tmp;
	char	*tmp2;

	tmp2 = get_env_value("PWD", (*env));
	tmp = getcwd(NULL, 0);
	oldpwd = ft_strjoin("=", tmp2);
	pwd = ft_strjoin("=", tmp);
	update_env("OLDPWD", oldpwd, env);
	update_env("PWD", pwd, env);
	free(pwd);
	free(tmp);
	free(tmp2);
	free(oldpwd);
	return (0);
}

int	cd(char **args, char ***env)
{
	char	*path;

	if (!args[1] || strcmp(args[1], "~") == 0 || args[1][0] == '\0')
		path = get_env_value("HOME", (*env));
	else
		path = args[1];
	if (chdir(path) == -1)
		return (print_error("cd", path, "No such file or directory"), 1);
	set_address(env);
	if (path != args[1])
		free(path);
	return (0);
}
