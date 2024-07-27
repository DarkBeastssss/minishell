/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amecani <amecani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 18:43:28 by amecani           #+#    #+#             */
/*   Updated: 2024/07/20 15:26:27 by amecani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>

char	*ft_strchr(const char *s, int c)
{
	char	*save_point;

	if (!s)
		return (NULL);
	c = c % 256;
	save_point = NULL;
	if (c == '\0')
	{
		while (*s)
			s++;
		return ((char *)s);
	}
	while (*s)
	{
		if (*s == c)
			return (save_point = (char *)s);
		s++;
	}
	return (0);
}

// char	*ft_strchr(const char *s, int c)
// {

// }

// int	main()
// {
// 	const char *s = "Busta";
// 	int c = 0;
// 	printf("%c\n",*ft_strchr(s,c));
// 	return (0);
// } 