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

int		ft_echo(char **argv);
int		ft_cd(char **argv, char **envp);
int		ft_pwd(void);
int		ft_env(char **argv, char **envp);
int		ft_exit(char **argv);
int		ft_export(char **argv, char ***envp);
int		ft_unset(char **argv, char ***envp);

char	*ft_getenv(char **envp, char *var);
char	*get_str(char **envp, char *reference);
void	err_msg(char *str);
void	*freedom(char ***arr);

#endif
