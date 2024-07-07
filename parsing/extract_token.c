/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amecani <amecani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 05:12:02 by amecani           #+#    #+#             */
/*   Updated: 2024/07/07 21:33:10 by amecani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//? If minishell lags I can just replace everything without the int i, so I work
//?		with pointers alone for efficency
void	iterate(char *s, int *i)
{
	char	quote;

	while (gap(s[*i]) && s[*i])
	{
		i++;
			if (!gap(s[*i + 1]) || !s[*i])
			{
				i++;
				return ;
			}
	}
	if (s[*i] == '\'' ||s[*i] == '\"')
		quote = s[*i];
	else
		quote = ' ';
	i++;
	while (s[*i] != quote)
	{
		if (!s[*i])
		{
			*i = UNCLOSED_QUOTES;
			return ;
		}
		i++;
	}
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
					break ;
				i++;
			}	
		}
		i++;
	}
	// printf("start : %d\n", start);
	// printf("i : %d\n", i);
	return (ft_substr(s, start, i));
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
