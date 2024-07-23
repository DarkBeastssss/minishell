# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bebuber <bebuber@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/06 21:57:45 by amecani           #+#    #+#              #
#    Updated: 2024/07/20 19:32:00 by bebuber          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.SILENT:

NAME = minishell

LIBDIR = ../libft
LIBFT = $(LIBDIR)/libft.a
HEADER = minishell.h

CC = cc
CFLAGS = -Wall -Werror -Wextra -g3

GREEN = "\033[32m"
RESET = "\033[0m"

SOURCES = \
			main.c \
			execute.c \
			$(addprefix ../builtins/, cd.c echo.c env.c export.c pwd.c unset.c exit.c)
OBJECTS = $(SOURCES:.c=.o)

all: $(LIBFT) $(NAME)

$(LIBFT):
	@echo $(GREEN)"Building libft..."$(RESET)
	@make -C $(LIBDIR)

$(NAME): $(OBJECTS) $(LIBFT)
	@echo $(GREEN)"Building $(NAME)..."$(RESET)
	@$(CC) $(CFLAGS) $(LIBFT) -o $(NAME) $(OBJECTS) -lreadline

%.o : %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo $(GREEN)"Cleaning up..."$(RESET)
	@make -C $(LIBDIR) clean
	@rm -f $(OBJECTS)

fclean: clean
	@echo $(GREEN)"Performing full clean..."$(RESET)
	@make -C $(LIBDIR) fclean
	@rm -f $(NAME)	

re: fclean all

.PHONY: all clean fclean re
