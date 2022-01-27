/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwillard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 16:41:32 by dwillard          #+#    #+#             */
/*   Updated: 2021/12/17 21:25:51 by dwillard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <minishell.h>

int main(int argc, char **argv, char **envp)
{
	char	*str[1000];
	int		index;

	index = 0;
	(void)argv;
	(void)argc;
	envp = ft_arrdup(envp, 0);
	ft_exclude(envp, "OLDPWD=");
	str[index] = readline("minishell$ ");
	while (str[index] && ft_strncmp(str[index], "exit", 4))
	{
		command_center(envp, str[index]);
		if (ft_strlen(str[index]) > 0)
			add_history(str[index]);
		index++;
		str[index] = readline("minishell$ ");
	}
	return (0);
}
