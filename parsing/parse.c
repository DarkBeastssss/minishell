/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amecani <amecani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 02:04:44 by amecani           #+#    #+#             */
/*   Updated: 2024/07/10 19:12:42 by amecani          ###   ########.fr       */
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

	if (close_quotes(s) == UNCLOSED_QUOTES)
		return (free(s), printf("Error! Unclosed quotes\n"), 0);
	token = init_deafult_token(NULL);
	if (!token)
		return (printf("m_error\n"), MALLOC_FAIL);
	i = 0;
	s = not_strchr(s, ' ');
	while (s)
	{
		extract_token_text_and_quote(s, &token); //! Extract Quote Next
		token->type		=	extract_token_type(token->string);//*fix after up quote and text extraction complete
		token->next		=	init_deafult_token(token);
		if (!token->next)
			return (free_tokens(token), printf("m_fail\n"), MALLOC_FAIL);
		s = not_strchr(s, ' ');
	}
	return (1);
}

static int	check_gaps_and_clear(char **s)
{
	if (!ft_strncmp(*s, "clear", 5) && \
			((*s[5] == ' ') || !*s[5]))
		return (free(*s), printf("\033[H\033[J"), 1);
	while (**s == ' ')
		if (!(**s + 1))
			return (free(*s), 1);
	// while (*s[i++] == ' ')
	// 	if (!s[i + 1])
	// 		return (free(*s), 1);
	return (0);
}

int	command_center(t_terminal_inputs **terminal)
{
	(*terminal)->input = readline("terminal :");
	add_history((*terminal)->input);
	if (!(*terminal)->input)
		return (CTRL_D);
	if (!check_gaps_and_clear(&(*terminal)->input)) //* Works
		return (1);
	if (!extract_token_characteristic(((*terminal)->input), NULL))
		return (1);
	return (55);
	// return (0);
}
