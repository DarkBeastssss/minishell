/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amecani <amecani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 02:04:44 by amecani           #+#    #+#             */
/*   Updated: 2024/07/10 12:22:11 by amecani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	display_tokens(t_token *token)
{
	while (token)
	{
		printf("string : %s\n", token->string);
		printf("type : %d\n", token->type);
		printf("quote_type : %c\n", token->quote_type);
		printf("\n");
		token = token->next;
	}
}

int	extract_token_characteristic(char *s, t_token *token)
{
	int		i;
	char	**array;

	if (close_quotes(s) == UNCLOSED_QUOTES)
		return (free(s), printf("Error! Unclosed quotes\n"), 0);
	token = init_deafult_token(NULL);
	if (!token)
		return (printf("m_error\n"), MALLOC_FAIL);
	i = 0;
	array = custom_split(s);
	while (array[i])
	{
		//! token->string	=	extract_token_text(&s[i]); Just fucking removve this
		token->type		=	extract_token_type(token->string);
		token->quote_type =	extract_quote_type(token);
		token->next		=	init_deafult_token(token);
		if (!token->next)
			return (free_tokens(token), MALLOC_FAIL);
	}
	return (1);
}

int	check_gaps_and_clear(char *s)
{
	int	i;

	if (!ft_strncmp(s, "clear", 5) && \
			(gap(s[5]) || !s[5]))
		return (free(s), printf("\033[H\033[J"), 1);
	i = 0;
	while (gap(s[i++]))
		if (!s[i + 1])
			return (free(s), 1);
	return (0);
}

int	command_center(t_terminal_inputs *terminal)
{
	terminal->input = readline("terminal :");
	add_history(terminal->input);
	if (!terminal->input)
		return (CTRL_D);
	if (check_gaps_and_clear(terminal->input)) //* Works
		return (1);
	if (!extract_token_characteristic(terminal->input, NULL))
		return (1);
	return (0);	
}
