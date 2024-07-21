/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_and_merge.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amecani <amecani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 12:55:42 by amecani           #+#    #+#             */
/*   Updated: 2024/07/21 18:21:37 by amecani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	should_it_merge(t_token **token)
{
	char	*joint;
	const t_token	*tmp = (*token);

	//? Take next token into first
	//? Then work with the free string or to where what

	(*token) = (*token)->next;
	(*token)->prev = tmp->prev;
	if (tmp->prev)
		tmp->prev->next = (*token);

	if (tmp->string && !tmp->next->string)
		tmp->next->string = tmp->string;
	else if (tmp->string && tmp->next->string)
	{
		joint = ft_strjoin(tmp->string, tmp->next->string);
		free(tmp->string);
		free(tmp->next->string);
		if (!joint)
			return (MALLOC_FAIL);
		tmp->next->string = joint;
	}

	return (free((t_token *)tmp), 1);
}


int	merge(t_token  **token)
// After merge the quote var, kinda becomes useless and uncorrect
//? Merge soul reason that exists, is that I did parsing wrong and I aint going to fix it
{
	get_first_token(token);
	while ((*token)->next)
	{
		if ((*token)->merge_with_next)
		{
			if(!should_it_merge(token))
			{
				get_first_token(token);
				return (free_tokens(*token), MALLOC_FAIL);
			}
		}
		else
			*token = (*token)->next;
	}
	//*// testing poupeses
	get_first_token(token);
	display_tokens(*token);
	get_first_token(token);
	//*/////////////////
	return (1);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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
			if (environ[array][i + 1] == '=' && \
			((search[i + 1] == '\0') || \
			(search[i + 1] == ' ') || \
			(search[i + 1] == '\'') || \
			(search[i + 1] == '$')) )
			return (&environ[array][i + 2]);
			i++;
		}
		array++;
	}
	return (NULL);
}

int	get_size(int env_content_size, char *s)
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
char *expansion(char *joint, char *content, char *s)
{
	const char *first_case = ft_strchr(s, '$');
	const char *first_joint = joint;
	const char *first_s = s;

	while (*s)
	{
		if (s == first_case)
		{
			s++;
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
	if (!content && !*first_joint)
		return (free((char *)(first_s)), NULL);
	return (free((char *)(first_s)), (char *)first_joint);
}//! Incase it doesnt free correctly, put the the (char *) outside

int	expand(t_token **token)
// if $(var) can be sepperated with : space, ' \"
{
	char *exp_content;

	get_first_token(token);
	while ((*token))
	{
		
		if (((*token)->quote != '\'') && ft_strchr((*token)->string, '$'))
		{
			exp_content = get_content((*token)->string);
			(*token)->string = expansion	(ft_calloc(sizeof(char), get_size(ft_strlen(exp_content), (*token)->string)), \
											exp_content, \
											(*token)->string);
		}
		else
		{
			if (!(*token)->next)
				break;
			(*token) = (*token)->next;
		}
	}
	return (1); //! do checks for all mallocs
}
