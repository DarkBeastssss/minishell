/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirectioning_v2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amecani <amecani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 13:44:09 by amecani           #+#    #+#             */
/*   Updated: 2024/07/30 20:39:10 by amecani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//? out < fd_input
//  cat < test
//  cat << a
//?       in > fd_output
//echo hello > test
//echo hello >> test

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
	line[ft_strlen(line) - 1] = '\0';
	// CTR-D
	while (ft_strcmp(line, exit))
	{
		line[ft_strlen(line)] = '\n';
		write (fd, line, ft_strlen(line));
		free(line);
		line = readline(">");
		if (!line)
			break;
		line[ft_strlen(line) - 1] = '\0';
	}
	return (free(line), fd);
}

void	update_fd(t_token **token, t_command **command)
{
	if ((*token)->type == OUT)
		(*command)->fd_out = out_case((*token)->next);
	if ((*token)->type == APPEND)
		(*command)->fd_out = append_case((*token)->next);
	else if ((*token)->type == IN)
		(*command)->fd_in = in_case((*token)->next);
	else if ((*token)->type == H_DOC)
		(*command)->fd_in = h_doc_case((*token)->next);
}

char	*first_redirection(t_token **token)
{
	t_token	*redrctn;

	redrctn = (*token);
	while (redrctn && redrctn->type != OUT && redrctn->type != H_DOC && redrctn->type != IN && redrctn->type != APPEND)
		redrctn = redrctn->next;
	if (redrctn == NULL)
		return (&(*token)->string[ft_strlen((*token)->string)]);
	return (redrctn->string);
}

int	redirectioning_v2(t_token **token, t_command **command)
{
	t_token		*first_t;
	t_command	*first_c;

	first_t = (*token);
	first_c = (*command);
	while ((*command))
	{
		(*command)->fd_in = -1;
		(*command)->fd_out = -1;
		update_fd(token, command);
		(*token) = (*token)->next;
		while ((*token) && ((*token)->type != OUT || (*token)->type != H_DOC || (*token)->type != IN || (*token)->type != APPEND))
			(*token) = (*token)->next;
		(*command) = (*command)->next;
	}
	first_redirection(&first_t)[0] = '\0';
	(*command) = first_c;
	(*token) = first_t;
	return (1);
}
