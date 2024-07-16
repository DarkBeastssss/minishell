/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amecani <amecani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 00:10:30 by amecani           #+#    #+#             */
/*   Updated: 2024/07/16 14:36:58 by amecani          ###   ########.fr       */
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
{
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

void spaceify(char **s, int len)
{
	while (len)
	{
		**s = ' ';
		(*s)++;
		len--;
	}
}

char *not_strchr(char *s, char ignore)
{
	while (*s)
	{
		if (*s != ignore)
			return (s);
		s++;
	}
	return (NULL);
}

t_token	*init_deafult_token(t_token *token)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (printf("m_error\n"),  NULL);
	// new->type = NULL; //! For Optimisation, even if you dont declate this here it
	// 				  //! will automatically be put as 0 (WORD)
	new->string	= NULL;
	new->quote	= 0;
	new->next	= NULL;
	new->prev	= token;
	return (new);
	//! okay so nvm without me initialising all these into NULL and 0, they automatically go like that (remove later the lines for opt)
}
