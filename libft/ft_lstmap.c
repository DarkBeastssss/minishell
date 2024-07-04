/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amecani <amecani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 13:49:23 by amecani           #+#    #+#             */
/*   Updated: 2023/11/10 15:24:39 by amecani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*elemtn;
	t_list	*uwu;
	void	*gtfouttahere;

	uwu = NULL;
	while (lst)
	{
		gtfouttahere = (f)(lst->content);
		elemtn = ft_lstnew(gtfouttahere);
		if (!elemtn)
		{
			del(gtfouttahere);
			ft_lstclear(&uwu, del);
			return (NULL);
		}
		ft_lstadd_back(&uwu, elemtn);
		lst = lst->next;
	}
	return (uwu);
}
