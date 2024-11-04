# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gholloco <gwendal.hollocou@orange.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/13 21:58:52 by gholloco          #+#    #+#              #
#    Updated: 2024/11/03 23:59:10 by gholloco         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC_DIR = src

SOURCES = main.c signals.c builtins/pwd.c builtins/env.c builtins/cd.c builtins/export.c builtins/echo.c \
		builtins/unset.c builtins/exit.c parsing/parse_line.c tools/error.c tools/2_split.c data.c parsing/expand.c \
		parsing/line_content.c tools/list_utils.c parsing/redirections.c exec/cmd_form.c exec/cmd_fd.c \
		tools/cmd_utils.c tools/str_utils.c exec/exec_p1.c exec/exec_p2.c exec/exec_p3.c exec/exec_builtins.c \
		tools/env_utils.c tools/besoindeplace_utils.c

OBJ_DIR = obj

OBJECT = $(SOURCES:%.c=%.o)

OBJECTS = $(addprefix $(OBJ_DIR)/, $(OBJECT))

LIBFT_DIR = ./includes/Libft

LIBFT = $(LIBFT_DIR)/libft.a

CC = cc

CFLAGS = -Wall -Werror -Wextra -g

RMFLAGS = -rf

all : $(OBJ_DIR) $(NAME)

$(NAME) : $(OBJECTS) $(LIBFT) 
	$(CC) $(CFLAGS) $^ -o $@ -lreadline

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR) :
	mkdir $(OBJ_DIR)

$(LIBFT) :  
	make -sC $(LIBFT_DIR) bonus

$(MLX) :
	make -sC $(MLX_DIR)

clean :
	rm $(RMFLAGS) $(OBJECTS)
	make -sC $(LIBFT_DIR) clean 

fclean : clean
	rm $(RMFLAGS) $(NAME)
	make -sC $(LIBFT_DIR) fclean

re : fclean all

PHONY = all clean fclean re

