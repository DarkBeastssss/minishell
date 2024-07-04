/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amecani <amecani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 02:04:41 by amecani           #+#    #+#             */
/*   Updated: 2024/07/04 23:01:05 by amecani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//? Checks if the character is a space or a tab
int	gap(char c)
{
	return (c == ' ' || c == '\t');
}

//! add this to parse_hub.c
int	check_gaps_and_clear(char *s)
{
	int	i;

	if (!ft_strncmp(s, "clear", 5) == 0 && \
			(gap(s[5] || !s[5])))
		return (free(s), printf("\033[H\033[J"), 0);
	i = 0;
	while (s[i++])
		if (!gap(s[i]) || !s[i + 1])
			return (0);
	return (1);
}


void	free_tokens(t_token *token)
{
	t_token	*temp;

	while (token)
	{
		if (token->string)
			free(token->string);
		token = token->prev;
		free(temp);
	}
}


int	extract_token_characteristics(char *s, t_token *token)
{
	int		i;
	char	quote_type;
	t_token	*new;

	i = 0;
	while (s[i])
	{
		new = malloc(sizeof(t_token));
		if (!new)
			return (free_tokens(token), printf("m_error\n"), BAD_RECIEVE);
		token = new;
		if (!i)
			token->prev = NULL;
		if (s[i] == '\'' || s[i] == '\"')
		{
			token->string = extract_string_within_quotes(); //! add this function
			quote_type = s[i];
			while (s[++i] != quote_type)
				i++;
		}
		else if (s[i] == '|')
			token->type = PIPE;
		else if (s[i] == '<')
			token->type = IN;
		else if (s[i] == '>')
			token->type = OUT;
		i++;
	}
}

int	command_center(t_terminal_inputs *terminal)
{
	terminal->input = readline("PROSI-shell$ :");
	add_history(terminal->input);
	if (!check_gaps_and_clear(terminal->input))
		return (BAD_RECIEVE);
	extract_token_characteristics(*terminal->input, terminal->input->token);
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