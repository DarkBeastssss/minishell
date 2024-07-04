/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amecani <amecani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 16:37:52 by amecani           #+#    #+#             */
/*   Updated: 2023/10/17 12:11:39 by amecani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*b_better;
	size_t			i;

	i = 0;
	b_better = (unsigned char *) b;
	while (i < len)
	{
		b_better[i] = c;
		i++;
	}
	return (b);
}

// int	main()
// {
// 	char	b[20] = "AOUGH!!!";
// 	int		c = '\0';
// 	size_t	len = 9;

// 	printf("%s\n",(char *)ft_memset((void *)b,c,len));
// 	return (0);
// }
// prob wrong lmeo 