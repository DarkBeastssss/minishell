/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amecani <amecani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 02:04:44 by amecani           #+#    #+#             */
/*   Updated: 2024/07/31 14:08:13 by amecani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	extract_token_characteristic(char *s, t_token **token)
{
	int		i;

	if (close_quotes(s) == UNCLOSED_QUOTES)
		return (printf("Error! Unclosed quotes\n"), 0);
	*token = init_deafult_token(NULL);
	if (!*token)
		return (printf("m_fail\n"), MALLOC_FAIL);
	i = 0;
	while (s[i] == ' ')
		i++;
	while (s[i])
	{
		(*token)->quote	=	extract_quote(&s[i]);
		i			    +=	extract_token_text(&s[i], token);
		(*token)->type		=	extract_token_type((*token)->string);
		while (s[i] == ' ')
			i++;
		if (!s[i])
			break;
		(*token)->next		=	init_deafult_token(*token);
		if (!(*token)->next)
			return (free_tokens(*token), printf("m_fail\n"), MALLOC_FAIL);
		*token = (*token)->next;
	}
	return (get_first_token(token), 1);
}

static int	check_gaps_and_clear(char *s)// its cuz its a copy
{
	//! Theres something here wrong but dc
	if (!s[0])
		return (1);
	if (!ft_strncmp(s, "clear", 5) && \
			((s[5] == ' ') || !s[5]))
		return (printf("\033[H\033[J"), 1);
	while (*s == ' ')
	{
		if (*
		(s + 1) == '\0') 
			return (1);
		s++;
	}
	return (0);
}

void	test_commands(t_command *cmmds)
{
	t_command	*first;
	int			i;

	first = cmmds;
	while (cmmds)
	{
printf("----------------TEST COMMANDS---------------\n");
		i = 0;
		printf("Command %d\n", i);
		printf("Command : %s\n", cmmds->args[i++]);
		printf("Args : ");
		while (cmmds->args[i])
			printf("%s--", cmmds->args[i++]);
		cmmds->fd_in = -1;
		cmmds->fd_out = -1;
		printf("fd_in: %d fd_out: %d\n", cmmds->fd_in, cmmds->fd_out);
		cmmds = cmmds->next;
	}
	cmmds = first;
}

int	command_center(t_data *data)
{
	data->input = readline("terminal :");
	data->token = NULL;
	data->cmmds = NULL;
	add_history(data->input);

	//? Nothing allocated		(besides data but thats free when program stops)
	if (!data->input)
		return (CTRL_D);
	//?

	//*	Input => freed outside function
	if (check_gaps_and_clear(data->input))
		return (1);
	if (!extract_token_characteristic(data->input, &data->token))
		return (1);
	//*

	// Input + (Token_struct + Token->string) => being freed
	if (!expand(&data->token, data->env))
		return (free_tokens(data->token), 1);
	if (!merge(&data->token))
		return (free_tokens(data->token), 1);
	if (!syntax_check(&data->token))
		return (free_tokens(data->token), 1);
	//

	//! Input + (Command_struct + Command-> array) + (Token_struct + Token->string) => being freed
	if (!redirectioning(&data->token, &data->cmmds))
		return (free_command_structs_and_double_array_only(data->cmmds), free_tokens(data->token), 1);
	if (!redirectioning_v2(&data->token, &data->cmmds))
		return (free_command_structs_and_double_array_only(data->cmmds), free_tokens(data->token), 1);
	//!

	// test_commands(data->cmmds);
	execute(data);
///////////////////////////////////////////////////////////////-
	free_tokens(data->token);
	free_command_structs_and_double_array_only(data->cmmds);
	return (0);
///////////////////////////////////////////////////////////////-
}
