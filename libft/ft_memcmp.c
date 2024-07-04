/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amecani <amecani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 12:11:23 by amecani           #+#    #+#             */
/*   Updated: 2023/10/22 15:42:08 by amecani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*o1;
	unsigned char	*o2;
	size_t			i;

	i = 0;
	o1 = (unsigned char *)s1;
	o2 = (unsigned char *)s2;
	while (i < n)
	{
		if (o1[i] != o2[i])
			return (o1[i] - o2[i]);
		i++;
	}
	return (0);
}

// int main()
// {
// 	const char *s1 = "O12";
// 	const char *s2 = "O";
// 	size_t n = 6;
// 	printf("%d\n",ft_memcmp(s1, s2, n));
// 	return (0);
// }