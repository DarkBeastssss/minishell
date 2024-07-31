/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amecani <amecani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 12:55:42 by amecani           #+#    #+#             */
/*   Updated: 2024/07/31 13:12:16 by amecani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool	not_a_var_char(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_' || (c >= '0' && c <= '9'))
		return (false);
	return (true);
}

char	*get_content(char *search, char **environ)
{
	char *debugg;
	int i;
	int array;

	search = ft_strchr(search, '$') + 1;
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
	int i = 0;
	char *first_intance = ft_strchr(s, '$');

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

// if u ask why its like this, OPTIMISATION ++ READIBILITY --
char *expansion(char *expanded_result, char *env_content, char *s, char *first_case)
{
	const char *first_expanded_result = expanded_result;
	const char *first_s = s;

	while (*s)
	{
		if (s++ == first_case)
		{
			while (*s != '$' && *s != ' ' && *s != '\0' && *s != '\'')
				s++;
			while (env_content && *env_content)
			{
				*expanded_result = *env_content;
				env_content++;
				expanded_result++;
			}
		}
		if (*s == '\0')
			break;
		*expanded_result = *s;
		expanded_result++;
		s++;
	}
	return (free((char *)(first_s)), (char *)first_expanded_result);
}

int	expand(t_token **token, char **environ)
{
	char	*env_content;
	char	*expanded_result;

	while ((*token))
	{
		if (((*token)->quote != '\'') && ft_strchr((*token)->string, '$'))
		{
			env_content = get_content((*token)->string, environ);
			expanded_result = ft_calloc(sizeof(char), get_size_v1(ft_strlen(env_content), (*token)->string));
			if (!expanded_result)
				return (free_tokens(*token), MALLOC_FAIL); 
			(*token)->string = expansion(expanded_result, env_content, (*token)->string, ft_strchr((*token)->string, '$'));
		}
		else
		{
			if (!(*token)->next)
				break;
			(*token) = (*token)->next;
		}
	}
	return (get_first_token(token), 1);
}
