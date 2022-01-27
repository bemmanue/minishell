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

void	init_info(char **envp)
{
	int	counter;

	counter = 0;
	g_info.std_fd[0] = dup(STDIN_FILENO);
	g_info.std_fd[1] = dup(STDOUT_FILENO);
	//сделать проверку на невыделение памяти
	g_info.env_lst = lst_new(envp[counter]);
	while (envp[++counter])
		lst_add_back(&(g_info.env_lst), lst_new(envp[counter]));
}

int	main(int argc, char **argv, char **envp)
{
	char	*str[1000];
	int		index;

	index = 0;
	(void)argv;
	(void)argc;
	envp = ft_arrdup(envp, 0);
	ft_exclude(envp, "OLDPWD=");
	init_info(envp);
	str[index] = readline("minishell$ ");
	while (str[index] && ft_strncmp(str[index], "exit", 4))
	{
		command_center(envp, str[index]);
		if (ft_strlen(str[index]) > 0)
			add_history(str[index]);
		free(str[index]);
		index++;
		if (index == 1000)
			index = 0;
		str[index] = readline("minishell$ ");
	}
	if (str[index])
		free(str[index]);
	return (0);
}
