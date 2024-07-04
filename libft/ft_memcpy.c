/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amecani <amecani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 14:54:58 by amecani           #+#    #+#             */
/*   Updated: 2023/10/29 19:48:08 by amecani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memcpy(void *restrict dst, const void *restrict src, size_t n)
{
	char		*dst_new;
	const char	*src_new;
	size_t		i;

	if (!dst && !src)
		return (NULL);
	src_new = (const char *)src;
	dst_new = (char *)dst;
	i = 0;
	while (i < n)
	{
		dst_new[i] = src_new[i];
		i++;
	}
	return (dst);
}

// #include <stdio.h>
// int main()
// {
// 	char src[3] = {'A','p','o'};
// 	char dst[3];

// 	ft_memcpy(dst,src,3);

// 	int i = 0;
// 	while (i < 3)
// 	{
// 		printf("%c",dst[i]);
// 		i++;
// 	}
// 	return (0);
// }