/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amecani <amecani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 02:04:44 by amecani           #+#    #+#             */
/*   Updated: 2024/07/20 14:29:06 by amecani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	extract_token_characteristic(char *s, t_token **token)
{//! doesnt handle "" and '' (empty quotes)
	int		i;

	if (close_quotes(s) == UNCLOSED_QUOTES)
		return (free(s), printf("Error! Unclosed quotes\n"), 0);
	*token = init_deafult_token(NULL);
	if (!*token)
		return (MALLOC_FAIL);
	i = 0;
	while (s[i] == ' ')
		i++;
	while (s[i])
	{
		(*token)->quote	=	extract_quote(&s[i]);
		i			    +=	extract_token_text(&s[i], token);
		(*token)->type		=	extract_token_type((*token)->string);
		if (!s[i])
			break;
		(*token)->next		=	init_deafult_token(*token);
		if (!(*token)->next)
			return (free_tokens(*token), printf("m_fail\n"), MALLOC_FAIL);
		*token = (*token)->next;
		while (s[i] == ' ')
			i++;
	}
	return (1);
}

static int	check_gaps_and_clear(char *s)// its cuz its a copy
{
	//! Theres something here wrong but dc
	if (!ft_strncmp(s, "clear", 5) && \
			((s[5] == ' ') || !s[5]))
		return (free(s), printf("\033[H\033[J"), 1);
	while (*s == ' ')
	{
		if (!*(s + 1)) 
			return (1);
		s++;
	}
	return (0);
}

int	command_center(t_data *data)
{
	data->input = readline("terminal :");
	data->token = NULL;
	add_history(data->input);
	if (!data->input)
		return (CTRL_D);
	if (check_gaps_and_clear(data->input))// Specific Check .1
		return (free(data->input), 1);
	if (!extract_token_characteristic(data->input, &data->token))
		return (free(data->input), 1);
	get_first_token(&data->token);
	if (!expand(&data->token))
		return (0); //! fix this later for mallocation error
	if (!merge(&data->token))
		return (free(data->input),1);
	return (0);
	// return (0);
}
