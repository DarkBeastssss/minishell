/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amecani <amecani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 12:50:03 by amecani           #+#    #+#             */
/*   Updated: 2023/10/30 15:39:46 by amecani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	original_len;
	char	*substring;

	original_len = ft_strlen(s);
	if (start >= original_len)
	{
		return (ft_strdup (""));
	}
	if (start + len > original_len)
	{
		len = original_len - start;
	}
	substring = (char *)malloc(len + 1);
	if (substring == NULL)
	{
		return (NULL);
	}
	ft_strlcpy(substring, s + start, len + 1);
	return (substring);
}
