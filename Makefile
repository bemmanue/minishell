# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dwillard <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/17 18:22:10 by dwillard          #+#    #+#              #
#    Updated: 2022/02/26 20:32:21 by bemmanue         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell

SRC_DIR		=	sources/
SRCS		=	pipex/redirects.c		shell/command_center.c	\
				shell/main.c			pipex/pipex.c			\
				shell/shell_utils.c		pipex/pipex_utils.c		\
				pipex/pipex_last.c		builtin/env.c			\
				builtin/exit.c			builtin/export.c		\
				builtin/cd.c			builtin/biltin_utils.c	\
				builtin/pwd.c			builtin/echo.c			\
				parser/parser.c			parser/parser_utils.c	\
				parser/command_line.c	parser/command.c		\
				parser/get.c			parser/expand.c			\
				parser/skip.c			builtin/unset.c			\
				shell/signals.c			pipex/here_doc.c

VPATH		=	$(SRC_DIR)
INCLUDES	=	sources/include.d/

OBJ_DIR		:=	build_files
OBJS 		=	$(patsubst %,$(OBJ_DIR)/%,$(SRCS:.c=.o))
DEPS		=	$(OBJS:.o=.d)

LIBFT		=	libft/
LIBFTMAKE	=	@$(MAKE) all -sC $(LIBFT)
LDFLAGS		=	-L$(HOME)/.brew/opt/readline/lib -I .brew/opt/readline/include

CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror -MMD

all:			lib $(NAME) $(BUILTIN)

$(OBJ_DIR)/%.o:	%.c
				@$(CC) -I$(LIBFT) -I$(INCLUDES) $(CFLAGS) -c $< -o $@
				@printf "\033[0;33mObject %-40.100s [\033[0;32m✔\033[0;33m]\r" $@

$(NAME):		$(OBJS)
				@$(CC) $(CFLAGS) $(OBJS) -Ilibft -L$(LIBFT) -lft\
 -I$(INCLUDES) -L$(HOME)/.brew/opt/readline/lib  -lreadline -o $(NAME)
				@printf '\033[1;32m%-100.100s\n\033[0m' '${NAME} compile success!'

$(OBJS):		| $(OBJ_DIR)

$(OBJ_DIR):
				@mkdir $(OBJ_DIR)
				@mkdir $(OBJ_DIR)/parser $(OBJ_DIR)/shell $(OBJ_DIR)/pipex\
 $(OBJ_DIR)/builtin

lib:
			$(LIBFTMAKE)

clean:
			@$(MAKE)	clean -sC $(LIBFT)
			@rm -rf $(OBJS) $(DEPS)
			@printf '\033[1;35mDelete objects success!\n\033[0m'

fclean:		clean
			@$(MAKE)	fclean -sC $(LIBFT)
			@rm -rf ${NAME}
			@rm -rf $(OBJ_DIR)
			@printf '\033[1;35mDelete ${NAME} success!\n\033[0m'

re:			fclean all
.PHONY:		all lib clean fclean re
-include	$(DEPS)
