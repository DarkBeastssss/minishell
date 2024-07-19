/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebuber <bebuber@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 15:41:01 by bebuber           #+#    #+#             */
/*   Updated: 2024/07/19 16:22:20 by bebuber          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_env_value(char *key, char **env)
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
				return (0);
			return (value);
		}
		i++;
	}
	return (0);
}

int	add_new_env(char *key, char *value, char ***env)
{
	int		i;
	int		j;
	char	**new_env;

	i = 0;
	while ((*env)[i])
		i++;
	new_env = malloc(sizeof(char *) * (i + 2));
	if (!new_env)
		return (1);
	j = 0;
	while (j < i)
	{
		new_env[j] = ft_strdup((*env)[j]);
		if (!new_env[j])
			return (1);
		j++;
	}
	new_env[j] = ft_strjoin(key, value);
	if (!new_env[j])
		return (1);
	new_env[j + 1] = NULL;
	free(*env);
	*env = new_env;
	return (0);
}

int	update_env(char *key, char *value, char ***env)
{
	int		i;
	int		ret;

	i = 0;
	while ((*env)[i])
	{
		if (strncmp((*env)[i], key, ft_strlen(key)) == 0)
		{
			free((*env)[i]);
			(*env)[i] = ft_strjoin(key, value);
			if (!(*env)[i])
				return (1);
			return (0);
		}
		i++;
	}
	ret = add_new_env(key, value, env);
	return (ret);
}

int	set_address(char **env)
{
	char	*oldpwd;
	char	*pwd;

	pwd = getcwd(NULL, 0);
	oldpwd = get_env_value("PWD", env);
	update_env("PWD=", pwd, &env);
	update_env("OLDPWD=", oldpwd, &env);
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
		print_error("cd", path, "No such file or directory");
	else
	{
		set_address(env);
		set_address(env);
	}
	return (0);
}
