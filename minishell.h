/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebuber <bebuber@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 03:04:51 by amecani           #+#    #+#             */
/*   Updated: 2024/07/27 13:14:27 by bebuber          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//? The ammount of .o files is annoying, perhaps create a sepparate folder and
//?				make the makefile ´put them all there instead

//! Handle the case where if < << > > | is first wrong, and if not sorrounded by
//!				a Word token wrong
//! Specific Check .2

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
	int				**fd;
	pid_t			*pid;
	int				exit_code;
	t_command		*cmmds;
	t_token			*token;
}					t_data;

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
int		command_center(t_data *terminal); //*/
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/

//!/////////	T O K E N	E X T R A C T I O N		//////////////!
int		extract_token_characteristic(char *s, t_token *token);	//!
//!//////////////////////////XD///////////////////////////////////!
int		extract_token_text(char *s, t_token **token);			//!
int		extract_token_type(char *s);							//!
char	extract_quote(char *s);									//!
int		close_quotes(char *s);									//!
//!///////////////////////////////////////////////////////////////!

//?/////		U T I L I T I E S		//////?
t_token	*init_deafult_token(t_token *token);//?
void	free_tokens(t_token *token);		//?
char	*not_strchr(char *s, char ignore);	//?
void	spaceify(char **s, int len);		//?
void	get_first_token(t_token **token);	//?
//?///////////////////////////////////////////?


////////////// builtins //////////////
//----> cd.c
int		cd(char **args, char **env);
char	*get_env_value(char *key, char **env);
//----> echo.c
int		echo(char **args);
//----> env.c
int		env(char **env, char **args);
int		update_env(char *key, char *value, char ***env);
int		add_new_env(char *key, char *value, char ***env);
void	free_arr(char **env);
//----> exit.c
int		ft_exit(t_command *cmmds, t_data *data);
void	print_error(char *command, char *arg, char *error);
//----> export.c
int		export(char **args, char ***env);
//----> pwd.c
int		pwd(char **args);
//----> unset.c
int		unset(char **env, char ***args);

////////////// execution //////////////
//----> execute.c
void	execute(t_data *data);
int		builtin_commands(char **args, t_data *data);
int		alloc_env(char ***env);
//----> exe_single.c
int		execute_single_command(t_data *data);
char	*find_path(char **env, char *command, t_data *data);
//----> exe_multiple.c
int		execute_multiple_commands(t_data *data);
//----> utils.c
void	free_all_pipes(int **fd, pid_t *pid, int nb_cmds);
void	close_all_pipes(int **fd, int nb_cmds);
int		count_commands(t_command *current);
int		ft_strcmp(const char *s1, const char *s2);

#endif

//! hi$user
//
//
//
// hello<<>"nah"'cuh'"again"