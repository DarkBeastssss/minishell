/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amecani <amecani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 00:10:30 by amecani           #+#    #+#             */
/*   Updated: 2024/07/31 17:07:45 by amecani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_command_structs_and_double_array_only(t_command *command)
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

t_command	*init_t_command(t_command *cmd)
{
	t_command	*new;

	new = ft_calloc(sizeof(t_command), 1);
	if (!new)
		return (NULL);
	new->prev = cmd;
	return (new);
}