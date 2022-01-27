/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwillard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 18:35:31 by dwillard          #+#    #+#             */
/*   Updated: 2021/12/20 21:32:30 by dwillard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include <fcntl.h>
# include <stdio.h>
# include <libft.h>

# define MAX_DIR 160

char	*get_str(char **envp, char *reference);

void	err_msg(char *str);

void	*freedom(char ***arr);

int		echo(int argc, char **argv);

int		cd(char **argv, char **envp);

int		pwd(void);

#endif
