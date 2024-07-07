/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amecani <amecani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 00:10:30 by amecani           #+#    #+#             */
/*   Updated: 2024/07/07 19:16:33 by amecani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	gap(char c)
{
	return (c == ' ' || c == '\t');
}

void	free_tokens(t_token *token)
{
	t_token	*temp;

	while (token)
	{
		free(token->string);
		temp = token;
		token = token->prev;
		free(temp);
	}
}

t_token	*init_deafult_token(t_token *token)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (printf("m_error\n"),  NULL);
	new->string = NULL;
	new->quote_type = 0;
	new->next = NULL;
	new->prev = token;
	return (new);
}
