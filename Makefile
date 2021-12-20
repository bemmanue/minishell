
NAME			=	minishell
CHECKER			=	checker

SRCS			=	sources/parser.c sources/command_center.c\
					sources/main.c sources/pipex.c\
					sources/shell_utils.c

OBJS			=	$(SRCS:.c=.o)

DEPS 			= 	$(SRCS:.c=.d)

HEAD			=	includes/push_swap.h
LIBFT			=	libft.a
LIBFT_PATH		=	./libft/
LIBFTMAKE		=	$(MAKE) all -sC $(LIBFT_PATH)
BUILTIN_PATH	=	sources/builtin/
CC				=	cc
CFLAGS			=	-Wall -Wextra -Werror -MMD

BUILTIN:			make -sC $(BUILTIN_PATH)

all:				lib $(NAME) $(BUILTIN)

bonus:				lib $(CHECKER)

.c.o:
					$(CC) $(CFLAGS) -Iincludes/ -c $< -o $@

$(NAME):			$(OBJS)
					$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT_PATH) -lft  -lreadline -o $(NAME)

lib:
					$(LIBFTMAKE)

clean:
					$(MAKE)	clean -sC $(LIBFT_PATH)
					rm -rf $(OBJS) $(DEPS)

fclean:				clean
					$(MAKE)	fclean -sC $(LIBFT_PATH)
					rm -rf $(NAME)

re:					fclean all
.PHONY:				all lib bonus clean fclean re
-include			$(OBJS:.o=.d) $(BNS_OBJS:.o=.d)
