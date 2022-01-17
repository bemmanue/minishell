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
        minishell.h
        libft/libft.h
        sources/builtin/builtin.h
    )

include_directories(.)

add_executable(
        minishell
        minishell.h
        sources/command_center.c
        sources/main.c
        sources/parser.c
        sources/pipex.c
        sources/shell_utils.c
        sources/builtin/cd.c
        sources/builtin/cd_utils.c
        sources/builtin/echo.c
        sources/builtin/pwd.c
        sources/builtin/builtin.h
        libft/libft.h
        libft/ft_split.c
        libft/ft_arrdup.c
        libft/ft_strdup.c
        libft/ft_strlen.c
        libft/ft_exclude.c
        libft/ft_strjoin.c
        libft/ft_strncmp.c
        libft/ft_putendl_fd.c
        libft/ft_putstr_fd.c
        libft/ft_memcpy.c
        libft/ft_calloc.c
        libft/ft_bzero.c
        sources/parse_example.c
        sources/redirects.c)

target_link_libraries(minishell readline)
