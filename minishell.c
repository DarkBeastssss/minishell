/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amecani <amecani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 02:04:41 by amecani           #+#    #+#             */
/*   Updated: 2024/07/03 03:21:31 by amecani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// add so if /// its red for wrong and ask potential teamate for new ones they might wanna add
int	main(int argc, char **argv, char **envp)
{
	if (argc != 1 && ft_strncp(argv[0], "./minishell", 11)) // add libft
		return (prif("Type only : './minishell' \n")); // colour ./minishell with cyan
	while ("the program is running")
		if (command_center() == BAD_RECIEVE)
			break ;
}