/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amecani <amecani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 18:40:37 by amecani           #+#    #+#             */
/*   Updated: 2023/10/29 17:30:02 by amecani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	size_finer(long long l)
{
	int	digits;

	digits = 0;
	if (!l)
		return (1);
	if (l < 0)
	{
		l = -l;
		digits++;
	}
	while (l)
	{
		digits++;
		l = l / 10;
	}
	return ((int)digits);
}

char	*ft_itoa(int n)
{
	long long	l;
	char		*ptr;
	int			size;

	if (!n)
		return (ft_strdup("0"));
	l = n;
	size = size_finer(l);
	ptr = (char *)malloc(size + 1);
	if (!ptr)
		return (NULL);
	if (n < 0)
	{
		ptr[0] = '-';
		l = -l;
	}
	ptr[size] = '\0';
	while ((size || l) && l > 0)
	{
		size--;
		ptr[size] = (l % 10) + 48;
		l = l / 10;
	}
	return (ptr);
}

// int main(int argc, char const *argv[])
// {
// 	printf("head = %s\n", ft_itoa(213));
// 	return 0;
// }
