
NAME			= 	parser

SRCS			=	parser.c	parser_utils.c	command_line.c	\
					main.c		command.c		get.c			\
					expand.c	skip.c			../shell_utils.c

OBJS			=	$(SRCS:.c=.o)

DEPS 			= 	$(SRCS:.c=.d)

LIBFT			=	libft.a
LIBFT_PATH		=	../../libft/
LIBFTMAKE		=	$(MAKE) all -sC $(LIBFT_PATH)
LDFLAGS			=	-L$(HOME)/.brew/opt/readline/lib

CC				=	cc
CFLAGS			=	-Wall -Wextra -Werror -MMD

all:				lib $(NAME) clean

.c.o:
					$(CC) $(CFLAGS) -I../include.d -I$(LIBFT_PATH) -c $< -o $@

$(NAME):			$(OBJS)
					$(CC) $(OBJS) -I../include.d -I$(LIBFT_PATH) -L$(LIBFT_PATH)\
					-lft $(LDFLAGS) -lreadline	-o $(NAME)

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
