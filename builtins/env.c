/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebuber <bebuber@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 18:34:57 by bebuber           #+#    #+#             */
/*   Updated: 2024/07/23 10:20:52 by bebuber          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_env(char ***env)
{
	int	i;

	i = 0;
	while ((*env)[i])
	{
		free((*env)[i]);
		i++;
	}
	free (*env);
	*env = NULL;
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
	printf("new_env[j]: %s\n", new_env[j]);
	free_env(env);
	return (*env = new_env, 0);
}

int	update_env(char *key, char *value, char ***env)
{
	int		i;
	int		ret;
	char	*tmp;

	i = 0;
	while ((*env)[i])
	{
		if (strncmp((*env)[i], key, ft_strlen(key)) == 0)
		{
			free ((*env)[i]);
			tmp = ft_strjoin(key, value);
			if (!tmp)
				return (1);
			(*env)[i] = tmp;
			printf("env[i]: %s\n", (*env)[i]);
			return (0);
		}
		i++;
	}
	ret = add_new_env(key, value, env);
	return (ret);
}

int	env(char **env, char **args)
{
	int		i;

	i = 1;
	while (args[i])
	{
		if (!ft_strchr(args[i], '=') || args[i][0] == '=')
		{
			print_error("env", args[i], "No such file or directory");
			return (1);
		}
		else if (ft_strchr(args[i], '='))
			i++;
	}
	i = 0;
	while (env[i])
	{
		if (ft_strchr(env[i], '='))
			ft_putendl_fd(env[i], 1);
		i++;
	}
	i = 1;
	while (args[i])
		ft_putendl_fd(args[i++], 1);
	return (0);
}
