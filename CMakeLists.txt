# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    CMakeLists.txt                                     :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dwillard <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/17 18:22:05 by dwillard          #+#    #+#              #
#    Updated: 2022/01/17 18:22:07 by dwillard         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

cmake_minimum_required(VERSION 3.20)
project(minishell C)

set(
        CMAKE_C_STANDARD 99
        libft/libft.h
        sources/include.d/minishell.h
        sources/include.d/logic.h
        sources/include.d/builtin.h
        sources/include.d/parser.h
        sources/include.d/include.h
    )

include_directories(
        sources/include.d
        libft
)

add_executable(
        minishell
        sources/include.d/minishell.h
        sources/include.d/builtin.h
        sources/include.d/parser.h
        sources/include.d/include.h
        sources/include.d/logic.h
        sources/shell/command_center.c
        sources/shell/main.c
        sources/pipex/pipex.c
        sources/shell/shell_utils.c
        sources/pipex/redirects.c
        sources/shell/signals.c
        sources/pipex/pipex_utils.c
        sources/builtin/cd.c
        sources/builtin/cd_utils.c
        sources/builtin/echo.c
        sources/builtin/pwd.c
        sources/builtin/env.c
        sources/builtin/unset.c
        sources/builtin/export.c
        sources/builtin/exit.c
        libft/ft_split.c
        libft/ft_arrlen.c
        libft/ft_arrdup.c
        libft/ft_strrchr.c
        libft/ft_isdigit.c
        libft/ft_atoul.c
        libft/ft_atol.c
        libft/ft_lstsize.c
        libft/ft_strcut.c
        libft/ft_strdup.c
        libft/ft_strndup.c
        libft/ft_isalpha.c
        libft/ft_strlen.c
        libft/ft_exclude.c
        libft/ft_strjoin.c
        libft/ft_strncmp.c
        libft/ft_putendl_fd.c
        libft/ft_putstr_fd.c
        libft/ft_memcpy.c
        libft/ft_calloc.c
        libft/ft_bzero.c
        libft/ft_free_arr.c
        libft/ft_unite.c
        libft/ft_lstadd_back.c
        libft/ft_lstclear.c
        libft/ft_strchr.c
        libft/ft_lstnew.c
        libft/ft_skipnchar.c
        libft/ft_itoa.c
        libft/ft_strcut.c
        libft/libft.h
        sources/parser/command.c
        sources/parser/command_line.c
        sources/parser/get.c
        sources/parser/expand.c
        sources/parser/parser.c
        sources/parser/parser_utils.c
        sources/parser/skip.c
        sources/pipex/pipex_last.c
        sources/pipex/here_doc.c)

target_link_libraries(minishell readline)
