/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebuber <bebuber@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 18:35:25 by bebuber           #+#    #+#             */
/*   Updated: 2024/07/19 15:29:24 by bebuber          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	export(char **env, char **args)
{
	int		i;
	int		j;
	char	*key;
	char	*value;

	if (!args[1])
		printexport(env);
	return (0);
}
