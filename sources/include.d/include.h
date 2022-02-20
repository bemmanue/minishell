/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   include.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwillard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 13:52:40 by dwillard          #+#    #+#             */
/*   Updated: 2022/02/20 13:52:41 by dwillard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INCLUDE_H
# define INCLUDE_H


typedef struct s_command
{
	char	*name;
	char	**argv;
	char	**rdrct;
	void	*next;
}			t_command;

typedef struct s_info
{
	int		std_fd[2];
	int		error;
	int		last_prcs;
	char	*file;
	char	*minidir;
	char	**env;
	char	**bltn;
}			t_info;

# include <stdio.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <string.h>
# include <signal.h>
# include <errno.h>
# include <err.h>
# include <stdbool.h>
# include <minishell.h>
# include <builtin.h>
# include <parser.h>
# include <libft.h>

#endif
