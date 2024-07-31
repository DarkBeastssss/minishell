/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirectioning_v2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amecani <amecani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 13:44:09 by amecani           #+#    #+#             */
/*   Updated: 2024/07/31 20:46:19 by amecani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
cat
NULL
file

> outpu.file echo < input.file hello world
echo < inout.file hello world
echo hello world >outpu.file < input.file
echo hello world NULL


> outpu.file echo < input.file hello world
outpu.file echo < input.file hello world
echo < input.file hello world
echo hello world

echo  adansd > oo < asdga
echo  adansd < asdga
echo  adansd
*/

static void	remove_from_array(char **args, int i)
{
	while (args[i] != NULL)
	{
		args[i] = args[i + 1];
		i++;
	}
}

static void	remove_redirections_argv(t_command *command, t_token *token)
{
	int		i;

	i = 0;
	while (command->args[i] != NULL)
	{
		if (token->type >= 3 && token->type <= 6)
		{
			remove_from_array(command->args, i);
			token = token->next;
			remove_from_array(command->args, i);
			token = token->next;
			continue ;
		}
		token = token->next;
		i++;
	}
}

int	redirectioning_v2(t_token **token, t_command **command)
{
	t_token		*first_t;
	t_command	*first_c;
	t_token		*i_need_it_i_swear;

	first_t = (*token);
	first_c = (*command);
	while ((*command))
	{
		(*command)->fd_in = -1;
		(*command)->fd_out = -1;
		i_need_it_i_swear = (*token);
		update_fd(token, command);
		remove_redirections_argv((*command), i_need_it_i_swear);
		(*command) = (*command)->next;
	}
	(*command) = first_c;
	(*token) = first_t;
	return (1);
}
