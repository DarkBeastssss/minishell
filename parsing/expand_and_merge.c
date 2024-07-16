/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_and_merge.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amecani <amecani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 12:55:42 by amecani           #+#    #+#             */
/*   Updated: 2024/07/16 15:37:54 by amecani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	should_it_merge(t_token **token)
{
	char	*joint;
	t_token	*tmp;

	joint = ft_strjoin((*token)->string, (*token)->next->string);
	if (!joint)
		return (MALLOC_FAIL);
	(*token)->merge_with_next = (*token)->next->merge_with_next;
	free((*token)->string);
	free((*token)->next->string);
	(*token)->string = joint;

	tmp = (*token)->next->next;
	free((*token)->next);
	(*token)->next = tmp;
	return (1);
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

// int	expand(char **env, t_token **token)
