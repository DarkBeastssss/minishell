/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amecani <amecani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 02:04:41 by amecani           #+#    #+#             */
/*   Updated: 2024/07/10 13:39:45 by amecani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **envp)
{
	t_terminal_inputs	*terminal;

	if (argc != 1)
		return (printf("Type only : './minishell' \n"));
	//
	terminal = malloc(sizeof(t_terminal_inputs));
	if (!terminal)
		return (printf("m_error\n"));
	terminal->env = envp;
	//
	while ("the program is running")
		if (command_center(&terminal) == CTRL_D)
			break ;
	return (free(terminal), 0);
}
