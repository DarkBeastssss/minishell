/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amecani <amecani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 00:10:30 by amecani           #+#    #+#             */
/*   Updated: 2024/07/31 22:22:47 by amecani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_command_and_array(t_command *command)
{
	t_command	*tmp;

	while (command->prev)
		command = command->prev;
	while (command)
	{
		tmp = command;
		command = command->next;
		free(tmp->args);
		free(tmp);
	}
}

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

void	free_tokens(t_token **token)
{
	t_token	*tmp;

	while ((*token)->next)
		(*token) = (*token)->next;
	while (*token)
	{
		tmp = (*token);
		(*token) = (*token)->prev;
		free(tmp->string);
		free(tmp);
	}
}
