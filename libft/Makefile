
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
			ft_skipchar.c		ft_skipnchar.c		ft_strcut.c		\
			ft_atoul.c			ft_arrlen.c			ft_strndup.c	\
			ft_free_strs.c		ft_isnumeric.c

OBJS = 		${SRCS:.c=.o}
DEPS =		${SRCS:.c=.d}
CC = 		clang
CFLAGS =	-Wall -Wextra -Werror -MMD -c

all: 		$(NAME)
.c.o:
			@$(CC) $(CFLAGS) $< -o $@
			@printf "\033[0;34mObject %-50.100s [\033[0;32m✔\033[0;34m]\r" $@

$(NAME): 	$(OBJS)
			@ar -rcs $(NAME) $?
			@printf '\033[1;32m%-100.100s\n\033[0m' 'libft compile success!'

clean:
			@rm -f $(OBJS) $(DEPS)


fclean: 	clean
			@rm -f $(NAME)
			@printf '\033[1;35mDelete libft success!\n\033[0m'

re:			fclean all

.PHONY:    	all clean fclean re
-include	$(OBJS:.o=.d)
