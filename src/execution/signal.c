/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebuber <bebuber@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 16:56:16 by bebuber           #+#    #+#             */
/*   Updated: 2024/07/31 21:07:20 by bebuber          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execution_handle(int sig)
{
	if (sig == SIGINT)
		printf("^C\n");
	else if (sig == SIGQUIT)
		printf("^\\Quit: 3\n");
}

void	newline(int sig)
{
	if (sig == SIGINT)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		write(1, "\n", 1);
		rl_redisplay();
	}
}

void   signal_handler(enum sig_mode mode)
{
	if (mode == EXECUTION)
	{
		signal(SIGINT, execution_handle);
		signal(SIGQUIT, execution_handle);
	}
	else if (mode == COMMAND)
	{
		signal(SIGINT, newline);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (mode == HEREDOC)
	{
		signal(SIGINT, newline);
		signal(SIGQUIT, SIG_IGN);
	}
}
