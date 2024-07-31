	/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amecani <amecani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 02:04:41 by amecani           #+#    #+#             */
/*   Updated: 2024/07/24 16:16:05 by amecani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **av, char **environ)
{
	t_data	*data;

	(void)av;

	if (argc != 1)
		return (printf("Type only : './minishell' \n"));
	data = ft_calloc(1, sizeof(t_data));
	if (!data)
		return (printf("m_error\n"), 1);
	alloc_env(&data->env, environ);
	while (command_center(data) != CTRL_D)
		free(data->input);
	free_arr(data->env);
	system("leaks minishell");
	return (0);
}
