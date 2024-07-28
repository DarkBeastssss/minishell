/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amecani <amecani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 12:55:42 by amecani           #+#    #+#             */
/*   Updated: 2024/07/28 00:20:41 by amecani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// void	split_token_into_more_tokens(t_token **token, char *s)
// {
// 	const	t_token *first = (*token);
// 	t_token	*new;

// 	while (*s == ' ')
// 		s++;
// 	new = init_deafult_token(first->prev);
// 	new->string = ft_substr((*token)->string , 0, integer_strchr(s, ' '));
// 	while (*s)
// 	{
// 		while (*s == ' ')
// 			s++;
// 		if (*s == '\0')
// 			break;
// 		new->next = init_deafult_token(new);
// 		new = new->next;
// 		//* printf("%s\n", new->string);
// 		//!protec malloc here !new
// 		new->string = ft_substr(s, 0, integer_strchr(s, ' '));
// 		while (*s != ' ' && *s != '\0')
// 			s++;
// 	}
// 	new->next = first->next;
// 	free(first->string);
// }


bool	not_a_var_char(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_' || (c >= '0' && c <= '9'))
		return (false);
	return (true);
}

char	*get_content(char *search)
{
	extern char			**environ;
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
char *expansion(char *joint, char *content, char *s, char *first_case)
{
	const char *first_joint = joint;
	const char *first_s = s;

	while (*s)
	{
		if (s++ == first_case)
		{
			while (*s != '$' && *s != ' ' && *s != '\0' && *s != '\'')
				s++;
			while (content && *content)
			{
				*joint = *content;
				content++;
				joint++;
			}
		}
		if (*s == '\0')
			break;
		*joint = *s;
		joint++;
		s++;
	}
	return (free((char *)(first_s)), (char *)first_joint);
}

int	expand(t_token **token)
{
	char	*exp_content;
	char	*new_str;
	//- int		dollar_pos;

	while ((*token))
	{
			//- dollar_pos = integer_strchr((*token)->string, '$');
		if (((*token)->quote != '\'') && ft_strchr((*token)->string, '$'))
		{
			exp_content = get_content((*token)->string);
			new_str = ft_calloc(sizeof(char), get_size_v1(ft_strlen(exp_content), (*token)->string));
			if (!new_str)
				return (free_tokens(*token), MALLOC_FAIL); 
			(*token)->string = expansion(new_str, exp_content, (*token)->string, ft_strchr((*token)->string, '$'));
			//- if (ft_strchr(exp_content, ' '))
			//- 	split_token_into_more_tokens(token, &(*token)->string[dollar_pos]); // do malloc error here
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
