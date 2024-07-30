/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amecani <amecani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 23:34:54 by amecani           #+#    #+#             */
/*   Updated: 2024/07/29 21:04:04 by amecani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	syntax_check(t_token **token)
{
	t_token *first = (*token);
	//what about them being the first one
	while ((*token))
	{
		if ((*token)->type == PIPE && \
		(!(*token)->prev || !(*token)->next || (*token)->prev->type != WORD || (*token)->next->type != WORD))
			return (free_tokens(*token), printf("Syntax error\n"), 0);
		if (((*token)->type == APPEND || (*token)->type == IN || (*token)->type == OUT || (*token)->type == H_DOC) \
		 && (!(*token)->prev || (*token)->prev->type != WORD))
			return (free_tokens(*token), printf("Syntax error\n"), 0);
		(*token) = (*token)->next;

		if ((*token)->next == NULL && \
			(*token)->type != EMPTY && (*token)->type != WORD && (*token)->type != EMPTY)
			return (printf("Syntax error near unexpected token `newline'\n"), free_tokens(first), 0); //! Fix Allocations free later
	}
	// //*// testing poupeses
	// get_first_token(token);
	// display_tokens(*token);
	// get_first_token(token);
	// //*/////////////////
	(*token) = first;
	return (1);
}
