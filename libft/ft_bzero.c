/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amecani <amecani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 14:56:34 by amecani           #+#    #+#             */
/*   Updated: 2023/10/17 13:18:01 by amecani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	ft_bzero(void *s, size_t n)
{
	size_t	i;
	char	*u;

	u = (char *)s;
	i = 0;
	while (i < n)
	{
		u[i++] = '\0';
	}
}

// #include <stdio.h>
// int main()
// {
// 	char name[3];

// 	ft_bzero(name,3);

// 	int i = 0;

// 	while (i < sizeof(name))
// 	{
// 		printf("%c",name[i]);
// 		i++;
// 	}

// 	return (0);
// }

// also dont forget oput void in memset 