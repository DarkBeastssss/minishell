/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amecani <amecani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 18:11:04 by amecani           #+#    #+#             */
/*   Updated: 2023/10/30 15:38:46 by amecani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		tni;
	char	*rahc;

	tni = 0;
	rahc = malloc(ft_strlen(s) + 1);
	if (!rahc)
		return (NULL);
	while (s[tni])
	{
		rahc[tni] = f(tni, s[tni]);
		tni ++;
	}
	rahc[tni] = '\0';
	return (rahc);
}

// Applies the function ’f’ to each character of the
// to create a new string (with malloc(3)) resulting
// from successive applications of ’f’.