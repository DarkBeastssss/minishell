/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amecani <amecani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 17:00:08 by amecani           #+#    #+#             */
/*   Updated: 2024/07/21 13:56:57 by amecani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		l;
	char	*joint;

	l = ft_strlen(s1) + ft_strlen(s2) + 1;
	joint = malloc(l * sizeof(char));
	if (!joint)
		return (NULL);
	ft_strlcpy(joint, s1, l);
	ft_strlcat(joint, s2, l);
	return (joint);
}
