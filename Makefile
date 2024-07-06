# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amecani <amecani@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/06 21:57:45 by amecani           #+#    #+#              #
#    Updated: 2024/07/06 22:36:18 by amecani          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
LIBFT = libft
CFLAGS = -Wall -Werror -Wextra -g3

SOURCES =				minishell.c \
$(addprefix parsing/,	extract_token.c parse.c utilities.c)

OBJECTS = $(SOURCES:.c=.o)

all: $(NAME)

$(LIBFT):
	@make -C libft

$(NAME): $(OBJECTS) | $(LIBFT)
	@$(CC) $(CFLAGS) $(LIBFT) $(OBJECTS) -o $(NAME)

%.o : %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean :
	@make -C includes/libft clean
	@rm -f $(OBJECTS)

fclean: clean
	@make -C includes/libft fclean
	@rm -rf $(OBJECTS)
	@rm -rf $(NAME)

re: fclean all