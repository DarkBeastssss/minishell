/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amecani <amecani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 05:12:02 by amecani           #+#    #+#             */
/*   Updated: 2024/07/06 21:52:44 by amecani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//? If minishell lags I can just replace everything without the int i, so I work
//?		with pointers alone for efficency
int	iterate_i(char *s)
{
	int		i;
	char	quote;

	i = 0;
	//(     'assdfdfa' ls -a "aa")
	while (gap(s[i]) && s[i])
	{
		i++;
		if (!gap(s[i]) || !s[i])
			return (i);
	}
	quote = ' ';
	if (s[0] == '\'' && s[0] == '\"')
		quote = s[0];
	i++;
	while (s[i] != quote && s[i])
	{
		i++;
		if (!s[i])
			return (i - i - UNCLOSED_QUOTES);
	}
	return (i);
}

char	*extract_token_text(char *s)
{
	int		i;
	int		start;
	char	quote_type;

	i = 0;
	while (s[i])
	{
		if (s[i] != ' ')
		{
			quote_type = ' ';
			if (s[i] == '\'' || s[i] == '\"' )
				quote_type = s[start];
			start = i;
			i += 2;
			while (s[i])
			{
				if (s[i] == quote_type)
					return (ft_substr(s, start, i));
				i++;
			}
		}
		i++;
	}
}

int	extract_token_type(char *s)
{
	if (!s[1])
	{
		if (s[0] == '|')
			return (PIPE);
		if (s[0] == '<') // << H_DOC
			return (IN);
		if (s[0] == '>') // >> APPEND
			return (OUT);
	}
	if (!s[2])
	{
		if (s[0] == '<' && s[1] == '<')
			return (H_DOC);
		if (s[0] == '>' && s[1] == '>')
			return (APPEND);
	}
	return (WORD);
}

char	extract_quote_type(t_token *token)
{
	if (token->type == WORD)
		if (token->string[0] == '\'' || token->string[0] == '\"')
			return (token->string[0]);
	return (0);
}
