# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bebuber <bebuber@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/06 21:57:45 by amecani           #+#    #+#              #
#    Updated: 2024/07/27 13:51:02 by bebuber          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.SILENT:

NAME = minishell

LIBFT = libft/libft.a
HEADER = minishell.h

CC = cc
CFLAGS = -Wall -Werror -Wextra -g3

SOURCES =				minishell.c \
$(addprefix builtins/,	cd.c echo.c env.c exit.c export.c pwd.c unset.c) \
$(addprefix execution/,	execute.c exe_single.c exe_multiple.c utils.c) \
$(addprefix parsing/,	extract_token.c parse.c utilities.c expand_and_merge.c)
OBJECTS = $(SOURCES:.c=.o)

all: $(LIBFT) $(NAME)

$(LIBFT):
	@make -C libft

$(NAME): $(OBJECTS) $(LIBFT)
	@$(CC) $(CFLAGS) $(LIBFT) -o $(NAME) $(OBJECTS) -lreadline

%.o : %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean :
	@make -C libft clean
	@rm -f $(OBJECTS)

fclean: clean
	@make -C libft fclean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re