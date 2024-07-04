/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amecani <amecani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 03:04:51 by amecani           #+#    #+#             */
/*   Updated: 2024/07/04 22:37:39 by amecani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// ! Add the code from github to school_repo

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"

# define BAD_RECIEVE -7

// Quote Types
# define SINGLE -1
# define DOUBLE -2

# include <readline/readline.h>

typedef enum s_type
{
	WORD,
	PIPE,
	IN,
	H_DOC,
	OUT,
	APPEND,
	ERR,
	END
}					t_type;

typedef struct s_token
{
	t_type			type;
	char			*string;
	struct s_token	*next;
	struct s_token	*prev;
}					t_token;

typedef struct s_terminal_inputs
{
	char			*input;
	char **env; //! add envp
}					t_terminal_inputs;

#endif