/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirectioning_v3_extra_fucntions.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amecani <amecani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 20:11:51 by amecani           #+#    #+#             */
/*   Updated: 2024/07/31 20:12:38 by amecani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	out_case(t_token *token)
{
	return (open(token->string, O_WRONLY | O_CREAT | O_TRUNC, 0644));
}

int	append_case(t_token *token)
{
	return (open(token->string, O_WRONLY | O_CREAT | O_APPEND, 0644));
}

int	in_case(t_token *token)
{
	return (open(token->string, O_RDONLY, 0644));
}

int	h_doc_case(t_token *token)
{
	const char	*exit = token->string;
	int			fd;
	char		*line;

	fd = open("h_doc.txt", O_WRONLY | O_CREAT | O_TRUNC, 0777);
	line = readline(">");
	while (ft_strcmp(line, exit))
	{
		write (fd, line, ft_strlen(line));
		write (fd, "\n", 1);
		free(line);
		line = readline(">");
		if (!line)
			break ;
	}
	close(fd);
	fd = open("h_doc.txt", O_RDONLY);
	return (free(line), fd);
}

void	update_fd(t_token **token, t_command **command)
{
	while ((*token) && (*token)->type != PIPE)
	{
		if ((*token)->type == OUT)
			(*command)->fd_out = out_case((*token)->next);
		else if ((*token)->type == APPEND)
			(*command)->fd_out = append_case((*token)->next);
		else if ((*token)->type == IN)
			(*command)->fd_in = in_case((*token)->next);
		else if ((*token)->type == H_DOC)
			(*command)->fd_in = h_doc_case((*token)->next);
		*token = (*token)->next;
	}
	if ((*token) && (*token)->type == PIPE)
		(*token) = (*token)->next;
}
