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

# include <libft.h>
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
# include <inttypes.h>

typedef struct s_command
{
	int		fd_redirs[2];
	char	*name;
	char	**argv;
	char	**rdrct;
	pid_t	pid;
	void	*next;
}			t_command;

typedef struct s_info
{
	uint8_t		sig;
	uint8_t		error;
	uint8_t		last_prcs;
	int32_t		std_fd[2];
	int32_t		*filed;
	t_command	*commands;
	char		*minidir;
	char		**env;
	char		**bltn;
}				t_info;

#endif
