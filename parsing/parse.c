/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amecani <amecani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 02:04:44 by amecani           #+#    #+#             */
/*   Updated: 2024/07/12 14:33:35 by amecani          ###   ########.fr       */
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

int	extract_token_characteristic(char *s, t_token *token)
{
	int		i;
		// wana see this fucntion
	if (close_quotes(s) == UNCLOSED_QUOTES)
		return (free(s), printf("Error! Unclosed quotes\n"), 0);
	token = init_deafult_token(NULL);
	if (!token)
		return (MALLOC_FAIL);
	i = 0;
	while (s[i] == ' ')
		i++;
	while (s[i])
	{
		token->quote	=	extract_quote(&s[i]);
		i			    +=	extract_token_text(&s[i], &token);
		token->type		=	extract_token_type(token->string);//*fix after up quote and text extraction complete
		if (!s[i])
			break;
		token->next		=	init_deafult_token(token);
		if (!token->next)
			return (free_tokens(token), printf("m_fail\n"), MALLOC_FAIL);
		token = token->next;
		while (s[i] == ' ')
			i++;
	}
	//*// testing poupeses
	while (token->prev)
		token = token->prev;
	display_tokens(token);
	//*/////////////////
	return (1);
}

static int	check_gaps_and_clear(char *s)// its cuz its a copy
{
	//! Theres something here wrong but dc
	if (!ft_strncmp(s, "clear", 5) && \
			((s[5] == ' ') || !s[5]))
		return (free(s), printf("\033[H\033[J"), 1);
	while (*s == ' ')
	{
		if (!*(s + 1)) 
			return (1);
		s++;
	}
	return (0);
}

int	command_center(t_terminal_inputs *terminal)
{
	terminal->input = readline("terminal :");
	add_history(terminal->input);
	if (!terminal->input)
		return (CTRL_D);
	if (check_gaps_and_clear(terminal->input))
		return (free(terminal->input), 1);
	if (!extract_token_characteristic((terminal->input), NULL))
		return (1);
	return (0);
	// return (0);
}
