/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebuber <bebuber@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 15:06:09 by bebuber           #+#    #+#             */
/*   Updated: 2024/07/11 15:40:52 by bebuber          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	echo(char **args)
{
	int	i;
	int	n_flag;

	i = 1;
	n_flag = 0;
	while (args[i])
	{
		if (!ft_strncmp(args[i], "-n", 2))
		{
			n_flag = 1;
			i++;
			continue ;
		}
		ft_putstr_fd(args[i], 1);
		if (args[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (!n_flag)
		ft_putstr_fd("\n", 1);
	return (0);
}
