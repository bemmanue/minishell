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

static char	**fill_bltn(void)
{
	char	**ret;
	int		i;

	i = 0;
	ret = ft_calloc(8, sizeof (char *));
	if (!ret)
		return (NULL);
	ret[0] = ft_strdup("echo");
	ret[1] = ft_strdup("cd");
	ret[2] = ft_strdup("pwd");
	ret[3] = ft_strdup("export");
	ret[4] = ft_strdup("unset");
	ret[5] = ft_strdup("env");
	ret[6] = ft_strdup("exit");
	while (i < 7)
		if (!ret[i])
			return (free_arr(&ret));
	return (ret);
}

static void	init_info(char **envp)
{
	int	counter;

	counter = 0;
	g_info.std_fd[0] = dup(STDIN_FILENO);
	g_info.std_fd[1] = dup(STDOUT_FILENO);
	//сделать проверку на невыделение памяти
	g_info.bltn = fill_bltn();
}

int	main(int argc, char **argv, char **envp)
{
	char	*str[1000];
	int		index;

	index = 0;
	(void)argv;
	(void)argc;
	g_info.env = ft_arrdup(envp, 0);
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
