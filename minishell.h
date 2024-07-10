/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amecani <amecani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 03:04:51 by amecani           #+#    #+#             */
/*   Updated: 2024/07/10 19:10:05 by amecani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"

# define CTRL_D		55
# define MALLOC_FAIL 0
# define UNCLOSED_QUOTES - 1


# include <stdio.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef enum s_type
{
	WORD,
	PIPE,
	IN,
	H_DOC,
	OUT,
	APPEND,
	ERR,
}					t_type;

typedef struct s_token
{
	t_type			type;
	char			*string;
	char			quote_type;
	struct s_token	*next;
	struct s_token	*prev;
}					t_token;

typedef struct s_terminal_inputs
{
	char			*input;
	char			**env;
}					t_terminal_inputs;

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
int		command_center(t_terminal_inputs **terminal);//*/
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/

//!/////////	T O K E N	E X T R A C T I O N		//////////////!
int		extract_token_characteristic(char *s, t_token *token);	//!
//!//////////////////////////XD///////////////////////////////////!
void	extract_token_text_and_quote(char *s, t_token **token);	//!
int		extract_token_type(char *s);							//!
char	extract_quote_type(t_token *token);						//!
int		close_quotes(char *s);									//!
//!///////////////////////////////////////////////////////////////!

//?/////		U T I L I T I E S		//////?
t_token	*init_deafult_token(t_token *token);//?
void	free_tokens(t_token *token);		//?
char	*not_strchr(char *s, char ignore);	//?
void	spaceify(char **s, int len);			//?
//?///////////////////////////////////////////?

#endif