/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amecani <amecani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 02:04:44 by amecani           #+#    #+#             */
/*   Updated: 2024/07/13 18:20:07 by amecani          ###   ########.fr       */
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
{//! doesnt handle "" and '' (empty quotes)
	int		i;

	if (close_quotes(s) == UNCLOSED_QUOTES)
		return (printf("Error! Unclosed quotes\n"), 0);
	token = init_deafult_token(NULL);
	if (!token)
		return (MALLOC_FAIL);
	i = 0;
	while (s[i] == ' ')
		i++;
	while (s[i])
	{
		token->quote	=	extract_quote(&s[i]);
		i			    +=	extract_token_text(&s[i], token);
		token->type		=	extract_token_type(token->string);
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
	get_first_token(&token);
	display_tokens(token);
	get_first_token(&token);
	//*/////////////////
	return (1);
}

static int	check_gaps_and_clear(char *s)// its cuz its a copy
{
	if (!s[0])
		return (1);
	//! Theres something here wrong but dc
	if (!ft_strncmp(s, "clear", 5) && \
			((s[5] == ' ') || !s[5]))
		return (printf("\033[H\033[J"), 1);
	while (*s == ' ')
	{
		if (!*(s + 1)) 
			return (1);
		s++;
	}
	return (0);
}

int	command_center(t_data data)
{
	t_data	data;

	data.input = readline("terminal :");
	data.token = NULL;
	add_history(data.input);
	if (!data.input)
		return (CTRL_D);
	if (check_gaps_and_clear(data.input))// Specific Check .1
		return (free(data.input), 1);
	if (!extract_token_characteristic(data.input, &data.token))
		return (free(data.input), 1);
	// first merge
	// if (!merge(data->input, data->token))
	// 	return (free(data->input), free_tokens(data->token),1);
	// if (!expand())
	// then expand
	return (0);
	// return (0);
}
