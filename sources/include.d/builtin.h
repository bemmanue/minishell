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

# include <include.h>

# define ARG_ERROR "too many arguments"
# define NUM_ERROR	"numeric argument required"

int		ft_pwd(void);
int		ft_cd(char **argv);
int		ft_env(char **argv);
int		ft_exit(char **argv);
int		ft_echo(char **argv);
int		ft_unset(char **argv);
int		ft_export(char **argv);

void	*freedom(char ***arr);
void	err_msg(char *str, int option);
char	*get_str(char **envp, char *reference);

#endif
