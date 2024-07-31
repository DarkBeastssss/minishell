/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amecani <amecani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 23:34:54 by amecani           #+#    #+#             */
/*   Updated: 2024/07/31 20:57:48 by amecani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	syntax_check(t_token **token)
{
	t_token	*first;

	first = (*token);
	while ((*token))
	{
		if ((*token)->next == NULL && \
			(*token)->type != EMPTY && (*token)->type != WORD && \
			(*token)->type != EMPTY)
		{
			(*token) = first;
			return (printf \
			("Syntax error near unexpected token `newline'\n"), 0);
		}
		if (((*token)->type >= 2) && \
		((*token)->prev == NULL && (*token)->next == NULL && \
		(*token)->prev->type <= 1 && (*token)->next->type <= 1))
		{
			(*token) = first;
			return (printf("Syntax error\n"), 0);
		}
		(*token) = (*token)->next;
	}
	(*token) = first;
	return (1);
}
