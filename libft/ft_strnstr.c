/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amecani <amecani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 15:44:12 by amecani           #+#    #+#             */
/*   Updated: 2023/10/29 19:45:41 by amecani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	needle_len;

	if (!needle[0])
		return ((char *)haystack);
	if (haystack[0])
	{
		needle_len = ft_strlen(needle);
		if (len == 0 || len < needle_len)
			return (NULL);
		while (*haystack && len >= needle_len)
		{
			if (ft_strncmp(haystack, needle, needle_len) == 0)
				return ((char *)haystack);
			haystack++;
			len --;
		}
	}
	return (NULL);
}

// int main()
// {
// 	const char haystack[] = "Chug Jug";
// 	const char needle[] = "Jug";
// 	size_t len = ft_strlen(haystack);
// 	char *result = ft_strnstr(haystack, needle, len);
// 	printf("%s", result);
// }