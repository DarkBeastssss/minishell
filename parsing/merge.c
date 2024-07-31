/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amecani <amecani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 00:16:39 by amecani           #+#    #+#             */
/*   Updated: 2024/07/31 13:36:33 by amecani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	should_it_merge(t_token **token)
// lowkey check later the fuck this monstrosity I have created
{
	char	*joint;
	const t_token	*tmp = (*token);

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
//? Merge soul reason that exists, is that I did parsing wrong and I aint going to fix it
{
	get_first_token(token);
	while ((*token)->next)
	{
		if ((*token)->merge_with_next)
		{
			if(!should_it_merge(token))
				return (get_first_token(token), MALLOC_FAIL);
		}
		else
			*token = (*token)->next;
	}
	return (get_first_token(token), 1);
}
