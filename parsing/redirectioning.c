/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirectioning.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amecani <amecani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 17:52:20 by amecani           #+#    #+#             */
/*   Updated: 2024/07/30 20:48:53 by amecani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_array_size(t_token **token)
{
	int	i;

	i = 0;
	while (*token)
	{
		if ((*token)->type == PIPE)
		{
			(*token) = (*token)->next;
			return (i + 1);
		}
		i++;
		(*token) = (*token)->next;
	}
	return (i + 1);
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

void	put_strings_in_array(char **args, t_token **token)
{
	int i;
	
	i = 0;
	while ((*token)->type != PIPE)
	{
		args[i] = (*token)->string;

		(*token) = (*token)->next;
		if ((*token) == NULL)
			return;
		i++;
	}
	(*token) = (*token)->next;
}


int	redirectioning(t_token **token, t_command **command)
{
	t_token *first = (*token);
	t_token *start;

	(*command) = init_t_command(NULL);
	if ((*command) == NULL)
		return (MALLOC_FAIL); //! fix later
	first = (*token);
	while (*token)
	{
		start = (*token);
		(*command)->args = ft_calloc(sizeof(char *), get_array_size(token));
		if ((*command)->args == NULL)
			return (MALLOC_FAIL); //! fix later
		(*token) = start;
		put_strings_in_array((*command)->args, token);
		if ((*token) == NULL)
			break;
		(*command)->next = init_t_command((*command));
		if ((*command)->next == NULL)
			return (MALLOC_FAIL); //! fix later
		(*command) = (*command)->next;
	}
	(*token) = first;
	get_first_cmnd(command);
	return(1);
}
