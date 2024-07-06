/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_hub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amecani <amecani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 02:04:44 by amecani           #+#    #+#             */
/*   Updated: 2024/07/06 05:09:38 by amecani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	extract_token_characteristic(char *s, t_token *token)
{
	int		i;

	i = 0;
	token = malloc(sizeof(t_token));
	if (!token)
		return (printf("m_error\n"), MALLOC_FAIL);
	token->prev = NULL;
	token->string = 0;
	token->quote_type = 0;
	while (s[i])
	{	// I can do a function like to do all of those at once
		token->string = extract_text(&s[i])
		token->type = extract_token_or_quote_type(token->string);
		i++;
	}
}
// split (space or ' or ")
 //? | > >> < << " '

int	check_gaps_and_clear(char *s)
{
	int	i;

	if (!ft_strncmp(s, "clear", 5) == 0 && \
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
	if (!extract_token_characteristic(*terminal->input, terminal->input->token))
		return (1);
}
