/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amecani <amecani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 02:04:41 by amecani           #+#    #+#             */
/*   Updated: 2024/07/04 15:25:45 by amecani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


//! add this to parse_hub.c
int	check_gaps_and_clear(char *s)
{
	int	i;

	if (!ft_strncmp(s, "clear", 5) == 0 && \
	(s[5] == '\0' || s[5] == ' ' || s[5] == '\t'))
		return (free(s), printf("\033[H\033[J"), 0);
	i = 0;
	while (s[i++])
		if (s[i] != ' ' || s[i] != '\t' || !s[i + 1])
			return (0);
	return (1);
}

int	command_center(t_terminal_inputs *terminal)
{
	terminal->input = readline("PROSI-shell$ :");
	add_history(terminal->input);
	if (!check_gaps_and_clear(terminal->input))
		return (BAD_RECIEVE);
}

int	main(int argc, char **argv, char **envp)
{
	t_terminal_inputs	*terminal;

	if (argc != 1) 										//! add libft
		return (prif("Type only : './minishell' \n"));	//! colour ./minishell with cyan
	while ("the program is running")
		if (command_center(terminal) == BAD_RECIEVE)
			break ;
}