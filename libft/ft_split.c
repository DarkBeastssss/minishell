/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amecani <amecani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 19:40:39 by amecani           #+#    #+#             */
/*   Updated: 2023/10/30 15:37:39 by amecani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	fill_me_up(char const *s, char c, int size, char **array)
{
	int	doesnt_matter;	
	int	i;
	int	len;

	doesnt_matter = 0;
	i = 0;
	while (!(size <= doesnt_matter))
	{
		len = 0;
		while (s[i] && s[i] == c)
			i++;
		while (s[i] && s[i] != c)
		{
			len++;
			i++;
		}
		array[doesnt_matter] = malloc((len + 1) * sizeof(char));
		if (!array[doesnt_matter])
			return (doesnt_matter + 1);
		ft_strlcpy (array[doesnt_matter], s + i - len, len + 1);
		doesnt_matter++;
	}
	return (0);
}

void	no(char **array, int bro)
{
	int	i;

	i = 0;
	while (i < bro)
	{
		free(array[i]);
		i++;
	}
	free (array);
}

size_t	counting_with_alban(char const *s, char c)
{
	size_t	word_count;

	word_count = 0;
	if (!(*s))
		return (0);
	while (*s)
	{
		while (*s == c)
			s++;
		word_count++;
		while (*s && *s != c)
			s++;
	}
	s--;
	if (*s == c)
		return (word_count - 1);
	return (word_count);
}

char	**ft_split(char const *s, char c)
{
	char	**array;
	size_t	size;
	int		bro;

	if (!s)
		return (NULL);
	size = counting_with_alban(s, c);
	array = malloc((size + 1) * sizeof(char *));
	if (!(array))
		return (0);
	if (size)
	{
		bro = fill_me_up(s, c, size, array);
		if (bro != 0)
		{
			no(array, bro);
			return (NULL);
		}
	}
	array[size] = NULL;
	return (array);
}

// int main(void)
// {
// 	char	*s = "1 2 3 4 5    6788  69 10";
// 	char	c = ' ';
// 	int i = 0;

// 	char **array = ft_split("\t\t\t\thello!\t\t\t\t", '\t');
// 	while (*array)
// 		printf("%d.%s.\n", ++i, *array++);
// 	return (0);
// }
