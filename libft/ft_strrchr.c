/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amecani <amecani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 13:20:01 by amecani           #+#    #+#             */
/*   Updated: 2023/10/29 18:32:39 by amecani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strrchr(const char *s, int c)
{
	char	*save_point;

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
			save_point = (char *)s;
		s++;
	}
	return (save_point);
}

// int main()
// {
// 	const char s[] = "CHUG JUp";
// 	int c = 'U';
// 	printf("%c",*ft_strrchr(s,c));
// 	return 0;
// }

// MAN SHIEET
// MAN SHIEET
// MAN SHIEET
// MAN SHIEET