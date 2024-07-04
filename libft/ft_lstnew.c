/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amecani <amecani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 17:26:42 by amecani           #+#    #+#             */
/*   Updated: 2023/11/09 17:53:59 by amecani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*skender;

	skender = malloc(sizeof(t_list));
	if (!skender)
		return (NULL);
	skender->content = content;
	skender->next = NULL;
	return (skender);
}
