/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amecani <amecani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 05:12:02 by amecani           #+#    #+#             */
/*   Updated: 2024/07/10 19:11:59 by amecani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


void	extract_token_text_and_quote(char *s, t_token **token)
{
	int		i = 0;
	char	sep = ' ';

	if ((s[0] == '<' && s[1] == '<') || (s[0] == '>' && s[1] == '>'))
	{
		(*token)->string = ft_substr(s, 0, 2);
		spaceify(&(*token)->string, 2);
	}
	else if (s[0] == '|' || s[0] == '>' || s[0] == '<')
	{
		(*token)->string = ft_substr(s, 0 , 1);
		spaceify(&(*token)->string, 1);
	}
	else
	{
		sep = s[0];
		if (sep == '\'' || sep == '\"')
		{
			i++;
			while (s[i + 1] != sep && s[i])
				i++;
			(*token)->string = ft_substr(s, 0, i);
			spaceify(&(*token)->string, i);
		}
		else
		{
			while (s[i] && !ft_strchr(" \'\"><|", s[i]))
				i++;
			(*token)->string = ft_substr(s, 0, i);
			spaceify(&(*token)->string, i);
		}
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
	char	*ptr;

	ptr = NULL;

	while (*s)
	{
		if (ptr == NULL && (*s == '\'' || *s == '\"'))
			ptr = s;
		if (s != ptr && ptr && *ptr == *s)
			ptr = NULL;
		s++;
	}
	if (ptr == NULL)
		return (1);
	return (UNCLOSED_QUOTES);
}
