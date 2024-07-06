/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amecani <amecani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 02:04:41 by amecani           #+#    #+#             */
/*   Updated: 2024/07/06 00:18:23 by amecani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_terminal_inputs	*terminal;

	if (argc != 1)
		return (prif("Type only : './minishell' \n"));
	while ("the program is running")
		if (command_center(terminal) == CTRL_D)
			break ;
}
