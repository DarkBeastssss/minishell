/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amecani <amecani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 00:10:30 by amecani           #+#    #+#             */
/*   Updated: 2024/07/21 15:17:50 by amecani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	display_tokens(t_token *token)
{
	printf("\n");
	while (token)
	{
		printf("string :	%s\n", token->string);
		printf("type :		%d\n", token->type);
		if (!token->quote)
			printf("quote_type :	none\n");
		else
			printf("quote_type :	%c\n", token->quote);
		printf("should_merge : %d\n", token->merge_with_next);
		printf("\n|||||||||||||||||\n\n");
		token = token->next;
	}
	printf("NULL\n");
}

void	get_first_token(t_token **token)
{
	while ((*token)->prev)
		(*token) = (*token)->prev;
}

void	free_tokens(t_token *token)
{ // fix free tokens at some point
// do get_first_token
// forgot do I need to give the ptr of the ptr?
	t_token	*temp;

	while (token)
	{
		free(token->string);
		temp = token;
		token = token->prev;
		free(temp);
		if (!token->next)
			printf("NULL");
	}
}

t_token	*init_deafult_token(t_token *token)
{
	t_token	*new;

	new = ft_calloc(sizeof(t_token), 1);
	if (!new)
		return (printf("m_error\n"),  NULL);
	new->prev	= token;
	return (new);
}

int	integer_strchr(char *s, char find)
{
	int	i;

	i = 0;
	while (s[i] != find && s[i])
		i++;
	return (i);
}