/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amecani <amecani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 00:10:30 by amecani           #+#    #+#             */
/*   Updated: 2024/07/11 17:45:27 by amecani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
