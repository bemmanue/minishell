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

t_info  g_info;

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
	{
		if (!ret[i])
			return (free_arr(&ret));
		i++;
	}
	return (ret);
}

static void	init_info(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	g_info.std_fd[0] = dup(STDIN_FILENO);
	g_info.std_fd[1] = dup(STDOUT_FILENO);
	g_info.bltn = fill_bltn();
	if (!g_info.bltn)
		return ;
	g_info.error = 0;
}

//void	ft_signal_cltr_c(int sig)
//{
//    (void) sig;
//    write(2, "\n", 1);
//    rl_on_new_line();
//    rl_replace_line("", 0);
//    rl_redisplay();
//}

void	set_signals(void)
{
//    signal(SIGQUIT, ft_signal_cltr_c);   // cntrl '\'
//    signal(SIGTERM, SIG_IGN);           // cntrl D
//    signal(SIGINT, ft_signal_cltr_c);   // cntrl C
}

int	main(int argc, char **argv, char **envp)
{
	char	*str[1000];
	int		index;

	index = 0;
	g_info.env = ft_arrdup(envp, 0); // можно отправить эту строку в init_info
	init_info(argc, argv);
	if (!g_info.env || !g_info.bltn)
		return (-1);
	envp = g_info.env;
	set_signals();
	str[index] = readline("minishell$ ");  // думаю, стоит выделить отдельную функцию для этого цикла, занимает слишком много места
	while (str[index])
	{
		command_center(envp, str[index]); // убрать envp из аргументов, т. к. он не используется
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
