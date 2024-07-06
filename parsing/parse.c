/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amecani <amecani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 02:04:44 by amecani           #+#    #+#             */
/*   Updated: 2024/07/06 22:25:43 by amecani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	extract_token_characteristic(char *s, t_token *token)
{
	int		i;

	token = init_deafult_token(NULL);
	if (!token)
		return (printf("m_error\n"), MALLOC_FAIL);
	i = 0;
	while (gap(s[i]))
		i++;
	while (s[i])
	{
		if (i == UNCLOSED_QUOTES)
			return (printf("Error! Unclosed quotes\n"), free(token), 0);
		// Extracting the characteristics of one token
		token->string	=	extract_token_text(&s[i]);
		token->type		=	extract_token_type(token->string);
		token->quote_type =	extract_quote_type(token);
		// Prepping new token
		token->next		=	init_deafult_token(token);
		if (!token->next)
			return (free_tokens(token), MALLOC_FAIL);
		// Iterating at the start of next token
		i += iterate_i(&s[i]);
	}
	return (1);
}
//	split (space or ' or ")
//?	| > >> < << " '

int	check_gaps_and_clear(char *s)
{
	int	i;

	if (!ft_strncmp(s, "clear", 5) && \
			(gap(s[5] || !s[5])))
		return (free(s), printf("\033[H\033[J"), 1);
	i = 0;
	while (s[i])
		if (!gap(s[i++]))
			return (0);
	return (1);
}

int	command_center(t_terminal_inputs *terminal)
{
	terminal->input = readline("PROSI-shell$ :");
	add_history(terminal->input);
	if (!terminal->input)
		return (CTRL_D);
	if (check_gaps_and_clear(terminal->input))
		return (1);
	if (!extract_token_characteristic(terminal->input, NULL))
		return (1);
	return (0);	
}
