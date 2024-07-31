/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebuber <bebuber@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 18:35:19 by bebuber           #+#    #+#             */
/*   Updated: 2024/07/31 17:21:26 by bebuber          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_env(char ***env, int loc)
{
	int		i;
	int		j;
	char	**new_env;

	i = 0;
	j = 0;
	while ((*env)[i])
		i++;
	new_env = malloc(sizeof(char *) * i);
	if (!new_env)
		return ;
	i = 0;
	while ((*env)[i])
	{
		if (i != loc)
		{
			new_env[j] = ft_strdup((*env)[i]);
			j++;
		}
		i++;
	}
	new_env[j] = NULL;
	free_arr(*env);
	*env = new_env;
}

int	is_valid_env_name(char *name, char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], name, ft_strlen(name)) && \
		((env[i][ft_strlen(name)] == '=') \
		|| (env[i][ft_strlen(name)] == '\0')))
			return (i);
		i++;
	}
	return (0);
}

int	unset(char ***env, char **args)
{
	int		i;
	int		loc;

	i = 1;
	loc = 0;
	while (args[i])
	{
		loc = is_valid_env_name(args[i], (*env));
		if (loc)
			remove_env(env, loc);
		i++;
	}
	return (0);
}
