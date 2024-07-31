/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amecani <amecani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 23:34:54 by amecani           #+#    #+#             */
/*   Updated: 2024/07/31 17:07:45 by amecani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	syntax_check(t_token **token)
{
	t_token *first = (*token);
	//what about them being the first one
	while ((*token))
	{
		if ((*token)->next == NULL && \
			(*token)->type != EMPTY && (*token)->type != WORD && (*token)->type != EMPTY)
		{
			(*token) = first;
			return (printf("Syntax error near unexpected token `newline'\n"), 0); //! Fix Allocations free later
		}
		if (((*token)->type == PIPE || (*token)->type == APPEND || (*token)->type == IN || (*token)->type == OUT || (*token)->type == H_DOC) && \
		((*token)->prev == NULL && (*token)->next == NULL && (*token)->prev->type != WORD && (*token)->next->type != WORD && (*token)->prev->type != EMPTY && (*token)->next->type != EMPTY))
		{
			(*token) = first;
			
			return (printf("Syntax error\n"), 0);
		}
		(*token) = (*token)->next;
	}
	(*token) = first;
	return (1);
}
