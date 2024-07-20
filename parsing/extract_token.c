/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amecani <amecani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 05:12:02 by amecani           #+#    #+#             */
/*   Updated: 2024/07/19 18:36:35 by amecani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


char	extract_quote(char *s)
{
	if (s[0] == '\'' || s[0] == '\"')
		return (s[0]);
	return (0);
}


int	extract_token_text(char *s, t_token **token)
{
	int		i = 0;
	char	sep = s[i];

	if ((s[0] == '<' && s[1] == '<') || (s[0] == '>' && s[1] == '>'))
		return ((*token)->string = ft_substr(s, 0, 2), 2);
	else if (s[0] == '|' || s[0] == '>' || s[0] == '<')
		return ((*token)->string = ft_substr(s, 0 , 1), 1);
	else
	{
		i++;
		if (sep == '\'' || sep == '\"')
		{
			while (s[i + 1] != sep && s[i])
				i++;
			(*token)->string = ft_substr(s, 1, i);
			i += 2;
		}
		else
		{
			while (s[i] && !ft_strchr(" \'\"><|", s[i]))
				i++;
			(*token)->string = ft_substr(s, 0, i);
		}
	}
	if (s[i] && !ft_strchr(" ><|", s[i]))
		(*token)->merge_with_next = true;
	return (i);
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
	else if (!s[2])
	{
		if (s[0] == '<' && s[1] == '<')
			return (H_DOC);
		if (s[0] == '>' && s[1] == '>')
			return (APPEND);
	}
	return (WORD);
}

int		close_quotes(char *s)
{
	char	*quote;

	quote = NULL;

	while (*s)
	{
		if (quote == NULL && (*s == '\'' || *s == '\"'))
			quote = s;
		if (s != quote && quote && *quote == *s)
			quote = NULL;
		s++;
	}
	if (quote == NULL)
		return (1);
	return (UNCLOSED_QUOTES);
}
