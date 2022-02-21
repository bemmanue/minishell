# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dwillard <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/17 18:22:10 by dwillard          #+#    #+#              #
#    Updated: 2022/02/20 13:54:02 by dwillard         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME		=	minishell

SRCS		=	sources/redirects.c				sources/command_center.c		\
				sources/main.c					sources/pipex.c					\
				sources/shell_utils.c			sources/pipex_utils.c			\
				sources/pipex_last.c			sources/builtin/env.c			\
				sources/builtin/exit.c			sources/builtin/export.c		\
				sources/builtin/cd.c			sources/builtin/cd_utils.c		\
				sources/builtin/pwd.c			sources/builtin/echo.c			\
				sources/parser/parser.c			sources/parser/parser_utils.c	\
				sources/parser/command_line.c	sources/parser/command.c		\
				sources/parser/get.c			sources/parser/expand.c			\
				sources/parser/skip.c			sources/builtin/unset.c			\
				sources/signals.c				sources/here_doc.c

OBJS		=	$(SRCS:.c=.o)

DEPS 		= 	$(SRCS:.c=.d)

LIBFT		=	libft.a
LIBFT_PATH	=	./libft/
LIBFTMAKE	=	$(MAKE) all -sC $(LIBFT_PATH)
LDFLAGS		=	-L$(HOME)/.brew/opt/readline/lib -I .brew/opt/readline/include

CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror -MMD

all:			lib $(NAME) $(BUILTIN)
.c.o:
				@$(CC) $(CFLAGS) -Ilibft -Isources/include.d -c $< -o $@
				@printf "\033[0;33mObject %-40.100s [\033[0;32m✔\033[0;33m]\r" $@

$(NAME):		$(OBJS)
				@$(CC) $(CFLAGS) $(OBJS) -Ilibft -Isources/include.d \
-L$(LIBFT_PATH) -lft $(LDFLAGS) -lreadline -o $(NAME)
				@printf '\033[1;32m%-100.100s\n\033[0m' '${NAME} compile success!'

lib:
			$(LIBFTMAKE)

clean:
			@$(MAKE)	clean -sC $(LIBFT_PATH)
			@rm -rf $(OBJS) $(DEPS)
			@printf '\033[1;35mDelete objects success!\n\033[0m'

fclean:		clean
			@$(MAKE)	fclean -sC $(LIBFT_PATH)
			@rm -rf ${NAME}
			@printf '\033[1;35mDelete ${NAME} success!\n\033[0m'

re:			fclean all
.PHONY:		all lib bonus clean fclean re
-include	$(OBJS:.o=.d) $(BNS_OBJS:.o=.d)
