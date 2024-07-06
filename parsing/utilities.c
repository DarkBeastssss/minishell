/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amecani <amecani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 00:10:30 by amecani           #+#    #+#             */
/*   Updated: 2024/07/06 04:52:49 by amecani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	gap(char c)
{
	return (c == ' ' || c == '\t');
}

void	free_tokens(t_token *token)
{
	t_token	*temp;

	while (token)
	{
		if (token->string)
			free(token->string);
		token = token->prev;
		free(temp);
	}
}

t_token	*init_deafult_token(t_token *token)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (printf("m_error\n"));
	new->prev = token;

	new->string = NULL;
	// token->next = new;
	new->next = NULL;
	return (new);
}

char	*extract_text(char *s)
{
	int		i;
	int		start;
	char	quote_type;

	i = 0;
	while (s[i])
	{
		if (s[i] != ' ')
		{
			quote_type = ' ';
			if (s[i] == '\'' || s[i] == '\"' )
				quote_type = s[start];
			start = i;
			i += 2;
			while (s[i])
			{
				if (s[i] == quote_type)
					return (ft_substr(s, start, i));
				i++;
			}
		}
		i++;
	}
}
