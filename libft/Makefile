
NAME =		libft.a

SRCS =		ft_atoi.c			ft_bzero.c 			ft_calloc.c 	\
			ft_isalnum.c 		ft_isalpha.c 		ft_isascii.c 	\
      		ft_isdigit.c 		ft_isprint.c 		ft_itoa.c 		\
      		ft_memccpy.c 		ft_memchr.c 		ft_memcmp.c 	\
      		ft_memcpy.c 		ft_memmove.c 		ft_memset.c 	\
			ft_putchar_fd.c 	ft_putendl_fd.c 	ft_putnbr_fd.c 	\
     		ft_putstr_fd.c 		ft_split.c 			ft_strchr.c 	\
    		ft_strdup.c 		ft_strjoin.c 		ft_strlcat.c 	\
    		ft_strlcpy.c 		ft_strlen.c 		ft_strmapi.c 	\
     		ft_strncmp.c 		ft_strnstr.c 		ft_strrchr.c 	\
      		ft_strtrim.c 		ft_substr.c 		ft_tolower.c 	\
      		ft_toupper.c		ft_atol.c			ft_exclude.c	\
      		ft_arrdup.c			ft_free_arr.c		ft_unite.c		\
			ft_lstadd_back.c 	ft_lstadd_front.c 	ft_lstclear.c 	\
     		ft_lstdelone.c 		ft_lstiter.c 		ft_lstlast.c 	\
			ft_lstmap.c			ft_lstnew.c			ft_lstsize.c	\
			ft_skipchar.c		ft_skipnchar.c		ft_strcut.c

OBJS = 		${SRCS:.c=.o}
DEPS =		${SRCS:.c=.d}
BNS_OBJS =	${BNS:.c=.o}
BNS_DEPS =	${BNS:.c=.d}
CC = 		clang
CFLAGS =	-Wall -Wextra -Werror -MMD -c

all: 		$(NAME)
.c.o:
		$(CC) $(CFLAGS) $< -o $@
$(NAME): 	$(OBJS)
		ar -rcs $(NAME) $?
bonus:
		make OBJS="$(BNS_OBJS)" all
clean:
		rm -f $(OBJS) $(BNS_OBJS) $(DEPS) $(BNS_DEPS)
fclean: 	clean
		rm -f $(NAME)
re:		fclean all
.PHONY:    	all bonus clean fclean re
-include			$(OBJS:.o=.d) $(BNS_OBJS:.o=.d)
