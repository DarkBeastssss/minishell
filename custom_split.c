/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amecani <amecani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 04:01:11 by amecani           #+#    #+#             */
/*   Updated: 2024/07/09 16:10:25 by amecani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	gap(char c)
{
	if (c == ' ')
		return (1);
	return (0);
}

int	find_size(char *s) // " " ' ' space
{
	int		i;
	int		size;
	char	sepperator;

	i = 0;
	size = 0;
	while (s[i])
	{
		sepperator = ' ';
		if (gap(s[i]) && s[i])
		{
			while (gap(s[i]))
				i++;
		}
		else if (s[i] == '\'' || s[i] == '\"')
		{
			sepperator = s[i];
			size++;
			i += 2;
			while (s[i - 1] != sepperator)
				i++;
		}
		else if (s[i] != ' ' && s[i])
		{
			size++;
			while (!gap(s[i]))
				i++;
		}
	}
	printf("size : %d\n", size);
	return (size);
}


char **custom_split(char *s)
{
	printf("%d\n", find_size(s));
	return NULL;
}

int main()
{
	custom_split("Im wished assd");
}
