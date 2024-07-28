/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirectioning.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amecani <amecani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 17:52:20 by amecani           #+#    #+#             */
/*   Updated: 2024/07/28 15:51:31 by amecani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_array_size(t_token **token)
{
	t_token *first = *token;
	int size;

	size = 0;
	while ((*token))
	{
		if ((*token)->type == PIPE)
			size++;
		(*token) = (*token)->next;
	}
	(*token) = first;
	return (size);
}

int	get_string_size(t_token **token)
{
	int i;
	int s;

	i = 0;
	while(*token)
	{
		s = 0;
		if ((*token)->type != PIPE)
		{
			while ((*token)->string[s++])
				i++;
			i++;
		}
		else
		{
			(*token) = (*token)->next;
			return (i);
		}
		(*token) = (*token)->next;
	}
	return (i);
}

char	**put_strings_in_array(char **args, t_token **token)
{
	int i;
	int	j;
	int	k;
	t_token *start;
	t_token *first = (*token);

	j = 0;
	while (*token)
	{
		i = 0;
		start = *token;
		args[j] = ft_calloc(sizeof(char), get_string_size(token) + 1);
		while (start && start->type != PIPE)
		{
			k = 0;
			while (start->string[k])
				args[j][i++] = start->string[k++];
			if (start->next && start->next->type != PIPE)
				args[j][i++] = ' ';
			start = start->next;
		}
		j++;
	}
	return (free_tokens(first), args);
}

t_command	*init_t_command(t_command *cmd)
{
	t_command	*new;

	new = ft_calloc(sizeof(t_command), 1);
	if (!new)
		return (NULL);
	new->prev	= cmd;
	return (new);
}

int	redirectioning(t_token **token, t_command **command)
{
	t_token *first;
	char **array;
	char *string;

	(*command) = init_t_command(NULL);
	if ((*command) == NULL)
		return (MALLOC_FAIL); //! fix later
	array = (*command)->args;
	first = (*token);
	array = ft_calloc(sizeof(char *), get_array_size(token) + 2);
	if (!array)
		return (free_tokens(*token), printf("m_error\n"), MALLOC_FAIL);
	array = put_strings_in_array(array, token);

	//*/TESTING PORPUSES//////////
	int i = 0;
	while (array[i])
	{
		printf(">%s<\n", array[i]);
		string = array[i++];
	}
	//*/TESTING PORPUSES//////////
	return(1);
}