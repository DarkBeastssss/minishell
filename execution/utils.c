/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebuber <bebuber@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 17:26:21 by bebuber           #+#    #+#             */
/*   Updated: 2024/07/23 10:35:18 by bebuber          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	int				i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

int	alloc_env(char ***env)
{
	int			i;
	int			len;
	extern char	**environ;

	i = 0;
	while (environ[i])
		i++;
	*env = (char **)malloc(sizeof(char *) * (i + 1));
	len = 0;
	i = 0;
	while (environ[i])
	{
		len = ft_strlen(environ[i]);
		(*env)[i] = (char *)malloc(sizeof(char) * (len + 1));
		if (!(*env)[i])
		{
			while (i >= 0)
				free((*env)[i--]);
			free(*env);
			return (ft_putendl_fd("Memory allocation failed", 2), 1);
		}
		ft_strlcpy((*env)[i], environ[i], len + 1);
		i++;
	}
	return ((*env)[i] = NULL, 0);
}
