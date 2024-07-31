/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amecani <amecani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 05:12:02 by amecani           #+#    #+#             */
/*   Updated: 2024/07/31 18:35:19 by amecani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


char	extract_quote(char *s)
{
	if (s[0] == '\'' || s[0] == '\"')
		return (s[0]);
	return (0);
}

bool	should_merge(char c)
{
	if (c && !ft_strchr(" ><|", c))
		return (true);
	return (false);
}

int	extract_token_text(char *s, t_token **token)
{
	int		i;
	const char	sep = s[0];

	if ((s[0] == '<' && s[1] == '<') || (s[0] == '>' && s[1] == '>'))
		return ((*token)->string = ft_substr(s, 0, 2),	2);
	else if(s[0] == '|' || s[0] == '>' || s[0] == '<')
		return ((*token)->string = ft_substr(s, 0 , 1),	1);
	else if ((s[0] == '\'' && s[1] == '\'') || (s[0] == '\"' && s[1] == '\"'))
		return ((*token)->string = NULL, (*token)->merge_with_next = should_merge(s[2]), 2);
	i = 1;
	if (sep == '\'' || sep == '\"')
	{
		while (s[i] != sep && s[i])
			i++;
		(*token)->string = ft_substr(s, 1, i - 1);
		i += 1;
	}
	else
	{
		while (s[i] && !not_a_var_char(s[i]))
			i++;
		(*token)->string = ft_substr(s, 0, i);
	}
	(*token)->merge_with_next = should_merge(s[i]);
	return (i);
}

int	extract_token_type(char *s)
{
	if (!s)
		return (EMPTY);
	if (!s[1])
	{
		if (s[0] == '|')
			return (PIPE);
		if (s[0] == '<')
			return (IN);
		if (s[0] == '>')
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
