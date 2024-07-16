/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amecani <amecani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 03:04:51 by amecani           #+#    #+#             */
/*   Updated: 2024/07/16 21:47:07 by amecani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//? The ammount of .o files is annoying, perhaps create a sepparate folder and
//?				make the makefile ´put them all there instead

//! Handle the case where if < << > > | is first wrong, and if not sorrounded by
//!				a Word token wrong
//! Specific Check .2

//! In the case of a mallocation error, I should be more  speccific, and print
//!				out that is malloc_error

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"

# define CTRL_D		55
# define MALLOC_FAIL 0
# define UNCLOSED_QUOTES - 1


# include <stdbool.h>
# include <stdio.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef enum s_type
{
	WORD,//*0
	PIPE,//*1
	IN,	//*2
	H_DOC,//*3
	OUT,//*4
	APPEND,//*5
	ERR,//*6
}					t_type;

typedef struct s_token
{
	t_type			type;
	char			*string;
	char			quote;
	bool			merge_with_next;
	struct s_token	*next;
	struct s_token	*prev;
}					t_token;

typedef struct s_commend
{
	char				**args;
	int					fd_in;
	int					fd_out;
	struct s_commend	*next;
	struct s_commend	*prev;
}					t_command;
typedef struct s_data
{
	char			*input;
	char			**env;
	int				exit_code;
	t_command		*cmmds;
	t_token			*token;
}					t_data;

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
int		command_center(t_data *terminal);//*/
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/

//!/////////	T O K E N	E X T R A C T I O N		//////////////!
int		extract_token_characteristic(char *s, t_token **token);	//!
//!//////////////////////////XD///////////////////////////////////!
int		extract_token_text(char *s, t_token **token);			//!
int		extract_token_type(char *s);							//!
char	extract_quote(char *s);									//!
int		close_quotes(char *s);									//!
//!///////////////////////////////////////////////////////////////!


//!//MERGE/MERGE/MERGE/MERGE/MERGE/MERGE/MERGE/MERGE/MERGE/MERGE//!
int		merge(t_token  **token);								//!
//!//MERGE/MERGE/MERGE/MERGE/MERGE/MERGE/MERGE/MERGE/MERGE/MERGE//!

//!EXPAND/EXPAND/EXPAND/EXPAND/EXPAND/EXPAND/EXPAND/EXPAND/EXPAND/!
int	expand(char **env, t_token **token);						//!
//!EXPAND/EXPAND/EXPAND/EXPAND/EXPAND/EXPAND/EXPAND/EXPAND/EXPAND/!


//?/////		U T I L I T I E S		//////?
t_token	*init_deafult_token(t_token *token);//?
void	free_tokens(t_token *token);		//?
int		integer_strchr(char *s, char find);	//?
void	get_first_token(t_token **token);	//?
void	display_tokens(t_token *token);		//?
//?///////////////////////////////////////////?

#endif
