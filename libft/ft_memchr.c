/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amecani <amecani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 12:21:42 by amecani           #+#    #+#             */
/*   Updated: 2023/10/30 15:32:33 by amecani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void	*ft_memchr(const void *src, int c, size_t n)
{
	unsigned char	*s;
	unsigned char	ch;
	int				i;

	i = 0;
	ch = (unsigned char) c;
	s = (unsigned char *)src;
	while (n-- > 0)
	{
		if (s[i] == ch)
			return ((void *)(s + i));
		i++;
	}
	return (NULL);
}

// int main()
// {
// 	const char *s = "Vamos!";
// 	int c = '!';
// 	size_t n = 7;

// 	printf("%p\n",ft_memchr(s,c,n));
// 	char* ret= (char *)ft_memchr(s,c,n);
// 	printf("%c\n",*ret);
// 	return (0);
// }