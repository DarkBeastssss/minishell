/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities_v2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amecani <amecani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 20:27:24 by amecani           #+#    #+#             */
/*   Updated: 2024/07/31 20:37:06 by amecani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*init_deafult_token(t_token *token)
{
	t_token	*new;

	new = ft_calloc(sizeof(t_token), 1);
	if (!new)
		return (NULL);
	new->prev = token;
	return (new);
}

int	integer_strchr(char *s, char find)
{
	int	i;

	i = 0;
	if (!s)
		return (-1);
	while (s[i])
	{
		if (s[i] == find)
			return (i);
		i++;
	}
	return (-1);
}

t_command	*init_t_command(t_command *cmd)
{
	t_command	*new;

	new = ft_calloc(sizeof(t_command), 1);
	if (!new)
		return (NULL);
	new->prev = cmd;
	return (new);
}