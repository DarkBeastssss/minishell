# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amecani <amecani@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/06 21:57:45 by amecani           #+#    #+#              #
#    Updated: 2024/07/31 17:14:31 by amecani          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# .SILENT:

NAME = minishell

LIBFT = libft/libft.a
HEADER = minishell.h

CC = cc
CFLAGS = -Wall -Werror -Wextra -g3 -I.

_SOURCES =				minishell.c \
$(addprefix builtins/,	cd.c echo.c env.c exit.c export.c pwd.c unset.c) \
$(addprefix execution/,	execute.c exe_single.c exe_multiple.c utils.c) \
$(addprefix parsing/,	extract_token.c parse.c utilities.c expand.c \
						merge.c syntax_check.c redirectioning.c \
						redirectioning_v2.c)
SOURCES = $(addprefix src/, $(_SOURCES))

OBJECTS = $(SOURCES:src/%.c=bin/%.o)

all: $(LIBFT) $(NAME)

$(LIBFT):
	@make -C libft --silent

$(NAME): $(OBJECTS) $(LIBFT)
	@$(CC) $(CFLAGS) $(LIBFT) -o $(NAME) $(OBJECTS) -lreadline

bin:
	@mkdir -p bin/builtins bin/parsing bin/execution

bin/%.o : src/%.c | bin
	@$(CC) $(CFLAGS) -c $< -o $@

clean :
	@make -C libft clean --silent
	@rm -f $(OBJECTS)

fclean: clean
	@make -C libft fclean --silent
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re