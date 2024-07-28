/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amecani <amecani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 00:10:30 by amecani           #+#    #+#             */
/*   Updated: 2024/07/28 21:54:53 by amecani          ###   ########.fr       */
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

void	get_first_cmnd(t_command **command)
{
	while ((*command)->prev)
		(*command) = (*command)->prev;
}

void	free_tokens(t_token *token)
{
	t_token	*temp;

	get_first_token(&token);
	while (token)
	{
		free(token->string);
		temp = token;
		token = token->next;
		free(temp);
	}
}

t_token	*init_deafult_token(t_token *token)
{
	t_token	*new;

	new = ft_calloc(sizeof(t_token), 1);
	if (!new)
		return (NULL);
	new->prev	= token;
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
		if(s[i] == find)
			return (i);
		i++;
	}
	return (-1);
}
