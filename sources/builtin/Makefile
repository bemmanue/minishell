NAME = built-in
CFLAGS = -Wall -Wextra -Werror
VARS = echo cd pwd export unset env exit
SRCS_DIR = sources/
SRCS = echo.c cd.c pwd.c export.c unset.c env.c exit.c

all: $(NAME)
$(NAME):
	mkdir ../../bin
	for index in $(VARS); do \
			cc $(CFLAGS) -I. $$index.c -o ../../bin/$$index ; \
			done
clean:
	rm -rf ../../bin
fclean: clean
re: fclean all
.PHONY: all clean fclean re built-in