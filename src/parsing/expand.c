/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amecani <amecani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 12:55:42 by amecani           #+#    #+#             */
/*   Updated: 2024/07/31 22:02:53 by amecani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	not_a_var_char(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') \
	|| c == '_' || (c >= '0' && c <= '9') || c == '?')
		return (false);
	return (true);
}

char	*get_content(char *search, char **environ, int exit_code)
{
	char	*debugg;
	int		i;
	int		array;

	search = ft_strchr(search, '$') + 1;
	if (search[0] == '?')
		return (ft_itoa(exit_code));
	array = 0;
	while (environ[array])
	{
		debugg = environ[array];
		i = 0;
		while (environ[array][i] == search[i])
		{
			if (environ[array][i + 1] == '=' && not_a_var_char(search[i + 1]))
				return (&environ[array][i + 2]);
			i++;
		}
		array++;
	}
	return (NULL);
}

int	get_size_v1(int env_content_size, char *s)
{
	int			i;
	const char	*first_intance = ft_strchr(s, '$');

	i = 0;
	while (*s)
	{
		if (s == first_intance)
		{
			s++;
			while (*s != ' ' && *s != '$' && *s != '\0')
				s++;
		}
		else
		{
			i++;
			s++;
		}
	}
	return (i + env_content_size + 1);
}

char	*expansion(char *expanded_result, \
char *env_content, char *token_str, char *first_case)
{
	int			i;

	first_case[0] = '\0';
	ft_strlcpy(expanded_result, token_str, first_case - token_str + 1);
	first_case[0] = '$';
	if (env_content)
		ft_strlcat(expanded_result, env_content,
			ft_strlen(env_content) + ft_strlen(expanded_result) + 1);
	i = 1;
	if (first_case[1] == '?')
		i++;
	else
	{
		while (ft_isdigit(first_case[1]) == false
			&& (ft_isalnum(first_case[i]) == true || first_case[i] == '_'))
			i++;
	}
	ft_strlcat(expanded_result, first_case + i,
		ft_strlen(first_case + i) + ft_strlen(expanded_result) + 1);
	free(token_str);
	if (first_case[1] == '?')
		free(env_content);
	return (expanded_result);
}

int	expand(t_token **token, char **environ, int exit_code)
{
	char	*env_content;
	char	*expanded_result;

	while ((*token))
	{
		if (((*token)->quote != '\'') && ft_strchr((*token)->string, '$'))
		{
			env_content = get_content((*token)->string, environ, exit_code);
			expanded_result = ft_calloc(sizeof(char), \
			get_size_v1(ft_strlen(env_content), (*token)->string));
			if (!expanded_result)
				return (free_tokens(token), MALLOC_FAIL);
			(*token)->string = expansion(expanded_result, env_content, \
			(*token)->string, ft_strchr((*token)->string, '$'));
		}
		else
		{
			if (!(*token)->next)
				break ;
			(*token) = (*token)->next;
		}
	}
	return (get_first_token(token), 1);
}
